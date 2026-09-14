#include "malloc.h"

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

static t_mallocCategory getCategory(size_t size)
{
	if (size <= HMALLOC_TINY_MAX)
		return (HMALLOC_CAT_TINY);
	if (size <= HMALLOC_SMALL_MAX)
		return (HMALLOC_CAT_SMALL);
	return (HMALLOC_CAT_LARGE);
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
	t_mallocCategory	category;
	size_t			alignedSize;

	if (size == 0)
		return (NULL);

	alignedSize = (size + HMALLOC_ALIGNMENT - 1) & ~(HMALLOC_ALIGNMENT - 1);

	hmallocMutexLock(&g_mallocState.mutex);

	category = getCategory(alignedSize);
	zoneList = getZoneList(alignedSize);
	block = findFreeBlock(category, alignedSize);

	if (!block) {
		newZone = createZone(getZoneSize(alignedSize), alignedSize, category);
		if (!newZone) {
			hmallocMutexUnlock(&g_mallocState.mutex);
			return (NULL);
		}
		addZoneToList(zoneList, newZone);
		block = findFreeBlock(category, alignedSize);
		if (!block) {
			hmallocMutexUnlock(&g_mallocState.mutex);
			return (NULL);
		}
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
