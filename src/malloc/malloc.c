#include "../../include/hmemory.h"

#include "malloc.h"
#include "tcache.h"

t_mallocState g_mallocState = {
	.tinyZones	= NULL,
	.smallZones	= NULL,
	.largeZones	= NULL,
	.mutex		= HMALLOC_MUTEX_INITIALIZER,
	.totalAlloc	= 0,
	.totalFree	= 0
};

static t_mallocZone **getZoneList(size_t size)
{
	if (size <= HMALLOC_TINY_MAX)
		return (&g_mallocState.tinyZones);
	else if (size <= HMALLOC_SMALL_MAX)
		return (&g_mallocState.smallZones);
	else
		return (&g_mallocState.largeZones);
}

static size_t getZoneSize(size_t size)
{
	size_t	alignedZoneHdr;
	size_t	blockTotal;

	if (size <= HMALLOC_TINY_MAX)
		return (HMALLOC_TINY_ZONE_SIZE);
	else if (size <= HMALLOC_SMALL_MAX)
		return (HMALLOC_SMALL_ZONE_SIZE);

	alignedZoneHdr = (sizeof(t_mallocZone) + HMALLOC_ALIGNMENT - 1)
					 & ~(HMALLOC_ALIGNMENT - 1);
	blockTotal = (sizeof(t_mallocBlock) + size + HMALLOC_ALIGNMENT - 1)
				 & ~(HMALLOC_ALIGNMENT - 1);
	return (alignedZoneHdr + blockTotal);
}

void *hmallocAllocInternal(size_t size)
{
	t_mallocZone	**zoneList;
	t_mallocZone	*newZone;
	t_mallocBlock	*block;
	size_t			alignedSize;

	if (size == 0)
		return (NULL);

	alignedSize = (size + HMALLOC_ALIGNMENT - 1) & ~(HMALLOC_ALIGNMENT - 1);

	hmallocMutexLock(&g_mallocState.mutex);

	zoneList = getZoneList(alignedSize);
	block = findFreeBlock(zoneList, alignedSize);

	if (!block) {
		newZone = createZone(getZoneSize(alignedSize), alignedSize);
		if (!newZone) {
			hmallocMutexUnlock(&g_mallocState.mutex);
			return (NULL);
		}
		addZoneToList(zoneList, newZone);
		block = newZone->blocks;
	}

	splitBlock(block, alignedSize);
	block->free = 0;
	g_mallocState.totalAlloc += block->size;

	hmallocMutexUnlock(&g_mallocState.mutex);

	return ((void *)(block + 1));
}


void hmallocFreeInternal(void *ptr)
{
	t_mallocBlock *block;

	if (!ptr)
		return;

	hmallocMutexLock(&g_mallocState.mutex);
	block = (t_mallocBlock *)ptr - 1;
	block->free = 1;
	g_mallocState.totalFree += block->size;
	coalesceBlocks(block);
	hmallocMutexUnlock(&g_mallocState.mutex);
}

/* --------------- Public malloc API using tcache --------------- */

void *malloc(size_t size)
{
	if (size == 0)
		return (NULL);

	/*
	 * Fast path: tcache.
	 * Align the size, compute the bin, and look at the cache.
	 * If a block is available, return it WITHOUT taking the global lock.
	 */
	int bin = tcacheSizeToBin(size);
	if (bin >= 0) {
		t_tcache *tc = tcacheGet();
		t_tcacheEntry *e = tc->bins[bin];
		if (e) {
			tc->bins[bin] = e->next;
			tc->counts[bin]--;
			/* Return the entry as-is: the block header is just before the
			 * user pointer, so the caller receives e (which points to the data). */
			return ((void *)e);
		}
		/*
		 * Empty cache: allocate a block via the internal allocator,
		 * then place it in the tcache for future mallocs of this size.
		 */
		void *p = hmallocAllocInternal(tcacheBinToSize(bin));
		return (p);
	}

	/*
	 * Slow path: size > TCACHE_MAX_SIZE.
	 * Go directly through the internal allocator.
	 */
	return (hmallocAllocInternal(size));
}

void free(void *ptr)
{
	if (!ptr)
		return;

	/*
	 * We need to recover the block size to know which bin to place it in.
	 * The header sits just before ptr.
	 */
	t_mallocBlock	*block = (t_mallocBlock *)ptr - 1;
	size_t			blockSize = block->size;

	int bin = tcacheSizeToBin(blockSize);
	if (bin >= 0) {
		t_tcache *tc = tcacheGet();
		if (tc->counts[bin] < TCACHE_MAX_PER_BIN) {
			/*
			 * Fast path: push into the tcache.
			 * No lock, no coalesce, no validateBlock.
			 *
			 * We reuse the `next` field of the block for chaining.
			 * Since the block is free, no one reads `next` except the
			 * tcache itself.
			 */
			t_tcacheEntry *e = (t_tcacheEntry *)ptr;
			e->next = tc->bins[bin];
			tc->bins[bin] = e;
			tc->counts[bin]++;
			return;
		}
		/*
		 * Full bin: flush ONE block back to the internal allocator to make room,
		 * then insert the new one.
		 */
		t_tcacheEntry *old = tc->bins[bin];
		tc->bins[bin] = old->next;
		tc->counts[bin]--;
		hmallocFreeInternal((void *)old);

		t_tcacheEntry *e = (t_tcacheEntry *)ptr;
		e->next = tc->bins[bin];
		tc->bins[bin] = e;
		tc->counts[bin]++;
		return;
	}

	/*
	 * Slow path: large allocation, go through the internal allocator.
	 */
	hmallocFreeInternal(ptr);
}

void *realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (malloc(size));

	if (size == 0) {
		free(ptr);
		return (NULL);
	}

	t_mallocBlock *block = (t_mallocBlock *)ptr - 1;
	size_t oldSize = block->size;
	size_t alignedSize = (size + HMALLOC_ALIGNMENT - 1) & ~(HMALLOC_ALIGNMENT - 1);

	/*
	 * Case 1: same tcache bin -> do not move.
	 * We can even grow/shrink within the same bin.
	 */
	int oldBin = tcacheSizeToBin(oldSize);
	int newBin = tcacheSizeToBin(alignedSize);
	if (oldBin >= 0 && newBin >= 0 && oldBin == newBin) {
		return (ptr);
	}

	/*
	 * Case 2: shrink within the same tcache bin -> keep it.
	 * (We do not return the slack, but we avoid a copy.)
	 */
	if (oldBin >= 0 && newBin >= 0 && newBin <= oldBin) {
		return (ptr);
	}

	/*
	 * Case 3: grow and the next block is free and large enough.
	 * Merge in place (call the internal allocator directly so we do not go
	 * back through the tcache).
	 */
	if (alignedSize > oldSize && block->next && block->next->free &&
		block->size + sizeof(t_mallocBlock) + block->next->size >= alignedSize)
	{
		hmallocMutexLock(&g_mallocState.mutex);
		block->size += sizeof(t_mallocBlock) + block->next->size;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
		splitBlock(block, alignedSize);
		hmallocMutexUnlock(&g_mallocState.mutex);
		return (ptr);
	}

	/*
	 * Case 4: allocate a new block and copy.
	 * Use the public malloc() (so tcache may be used).
	 */
	void *newPtr = malloc(size);
	if (!newPtr)
		return (NULL);

	size_t copySize = (oldSize < size) ? oldSize : size;
	ft_memcpy(newPtr, ptr, copySize);
	free(ptr);

	return (newPtr);
}

void *calloc(size_t nmemb, size_t size)
{
	size_t totalSize;
	void *ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);

	totalSize = nmemb * size;
	if (nmemb != totalSize / size)
		return (NULL);

	/*
	 * For sizes handled by the tcache, we can zero only the requested
	 * portion. Tcache blocks may contain stale data, so zeroing is REQUIRED.
	 */
	ptr = malloc(totalSize);
	if (!ptr)
		return (NULL);

	ft_bzero(ptr, totalSize);
	return (ptr);
}
