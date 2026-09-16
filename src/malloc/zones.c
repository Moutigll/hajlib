#include "malloc.h"
#include "mallocos.h"

static t_mallocBlock **getBinsForCategory(t_mallocCategory cat)
{
	if (cat == HMALLOC_CAT_TINY)
		return (g_mallocState.tinyFreeBins);
	else if (cat == HMALLOC_CAT_SMALL)
		return (g_mallocState.smallFreeBins);
	return (NULL);
}

static inline int segBinIndex(size_t size)
{
	if (size > HMALLOC_SEG_MAX_EXACT)
		return (HMALLOC_SEG_NUM_BINS - 1);
	return ((int)((size + HMALLOC_SEG_ALIGNMENT - 1) / HMALLOC_SEG_ALIGNMENT) - 1);
}

static void freeListPush(t_mallocBlock *block)
{
	if (!block)
		return;

	if (block->category == HMALLOC_CAT_LARGE) {
		block->freeNext = g_mallocState.largeFreeList;
		block->freePrev = NULL;
		if (g_mallocState.largeFreeList)
			g_mallocState.largeFreeList->freePrev = block;
		g_mallocState.largeFreeList = block;
		block->binIdx = 0;
		return;
	}

	t_mallocBlock **bins = getBinsForCategory(block->category);
	int bin = segBinIndex(block->size);

	block->freeNext = bins[bin];
	block->freePrev = NULL;
	if (bins[bin])
		bins[bin]->freePrev = block;
	bins[bin] = block;
	block->binIdx = bin;
}

void freeListRemove(t_mallocBlock *block)
{
	if (block->binIdx < 0)
		return;

	if (block->category == HMALLOC_CAT_LARGE) {
		if (block->freePrev)
			block->freePrev->freeNext = block->freeNext;
		else
			g_mallocState.largeFreeList = block->freeNext;
	} else {
		t_mallocBlock **bins = getBinsForCategory(block->category);
		if (block->freePrev)
			block->freePrev->freeNext = block->freeNext;
		else
			bins[block->binIdx] = block->freeNext;
	}
	if (block->freeNext)
		block->freeNext->freePrev = block->freePrev;

	block->freeNext = NULL;
	block->freePrev = NULL;
	block->binIdx = -1;
}


t_mallocZone *createZone(size_t zoneSize, size_t blockSize, t_mallocCategory category)
{
	t_mallocZone	*zone;
	t_mallocBlock	*block;
	t_mallocBlock	*prev;
	size_t			blockCount, i, offset, blockTotal;

	zone = hmallocMap(zoneSize);
	if (!zone)
		return (NULL);

	zone->size = zoneSize;
	zone->blocks = NULL;
	zone->next = NULL;
	zone->category = category;

	offset = sizeof(t_mallocZone);
	offset = (offset + HMALLOC_ALIGNMENT - 1) & ~(HMALLOC_ALIGNMENT - 1);
	blockTotal = sizeof(t_mallocBlock) + blockSize;
	blockTotal = (blockTotal + HMALLOC_ALIGNMENT - 1) & ~(HMALLOC_ALIGNMENT - 1);
	blockCount = (zoneSize - offset) / blockTotal;
	if (blockCount == 0)
		blockCount = 1;

	prev = NULL;
	for (i = 0; i < blockCount; i++)
	{
		block = (t_mallocBlock *)((char *)zone + offset);
		block->size = blockSize;
		block->free = 1;
		block->category = category;
		block->binIdx = -1;
		block->freeNext = NULL;
		block->freePrev = NULL;
		block->prev = prev;
		block->next = NULL;

		if (prev)
			prev->next = block;
		else
			zone->blocks = block;

		freeListPush(block);

		prev = block;
		offset += blockTotal;
	}
	return (zone);
}

void	addZoneToList(t_mallocZone **list, t_mallocZone *zone)
{
	if (!zone)
		return;
	zone->next = *list;
	*list = zone;
}

t_mallocBlock *findFreeBlock(t_mallocCategory category, size_t size)
{
	if (category == HMALLOC_CAT_LARGE)
	{
		t_mallocBlock *block = g_mallocState.largeFreeList;
		while (block)
		{
			if (block->size >= size)
				{
					freeListRemove(block);
					return (block);
				}
			block = block->freeNext;
		}
		return (NULL);
	}

	t_mallocBlock **bins = getBinsForCategory(category);
	int bin = segBinIndex(size);
	int overflow = HMALLOC_SEG_NUM_BINS - 1;

	if (bin < overflow)
	{
		/* Exact bins: each bin `k` contains blocks with exactly size k*16.
		 * If the exact bin is empty, also try a few higher bins
		 * (leftovers from splitBlock that are slightly larger than requested). */
		int limit = bin + HMALLOC_SEG_SEARCH_LIMIT;
		if (limit > overflow - 1)
			limit = overflow - 1;
		for (int b = bin; b <= limit; b++)
			if (bins[b]) {
				t_mallocBlock *block = bins[b];
				freeListRemove(block);
				return (block);
			}
	}

	/* Request > HMALLOC_SEG_MAX_EXACT, or nothing was found in the exact bins:
	 * use first-fit on the overflow bin (few blocks in practice). */
	t_mallocBlock *block = bins[overflow];
	while (block)
	{
		if (block->size >= size)
		{
			freeListRemove(block);
			return (block);
		}
		block = block->freeNext;
	}
	return (NULL);
}

void splitBlock(t_mallocBlock *block, size_t size)
{
	t_mallocBlock *newBlock;

	if (!block || block->size <= size + sizeof(t_mallocBlock))
		return;

	newBlock = (t_mallocBlock *)((char *)(block + 1) + size);
	newBlock->size = block->size - size - sizeof(t_mallocBlock);
	newBlock->next = block->next;
	newBlock->prev = block;
	newBlock->free = 1;
	newBlock->category = block->category;
	newBlock->binIdx = -1;

	block->size = size;
	block->next = newBlock;
	if (newBlock->next)
		newBlock->next->prev = newBlock;

	freeListPush(newBlock);
}

void coalesceBlocks(t_mallocBlock *block)
{
	if (!block)
		return;

	if (block->prev && block->prev->free)
	{
		t_mallocBlock *prev = block->prev;
		t_mallocBlock *next = block->next;

		freeListRemove(prev);

		prev->size += sizeof(t_mallocBlock) + block->size;
		prev->next = next;
		if (next)
			next->prev = prev;
		block->prev = NULL;
		block->next = NULL;
		block->size = 0;
		block = prev;
	}

	if (block->next && block->next->free)
	{
		t_mallocBlock *next = block->next;

		freeListRemove(next);

		block->size += sizeof(t_mallocBlock) + next->size;
		block->next = next->next;
		if (block->next)
			block->next->prev = block;
		next->prev = NULL;
		next->next = NULL;
		next->size = 0;
	}

	block->free = 1;
	block->binIdx = -1;
	block->freeNext = NULL;
	block->freePrev = NULL;
	freeListPush(block);
}
