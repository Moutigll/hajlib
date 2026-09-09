#include "../../include/hmemory.h"

#include "malloc.h"

t_mallocState	g_mallocState = {
	.tinyZones	= NULL,
	.smallZones	= NULL,
	.largeZones	= NULL,
	.mutex		= PTHREAD_MUTEX_INITIALIZER,
	.totalAlloc	= 0,
	.totalFree	= 0
};

static t_mallocZone	**getZoneList(size_t size)
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
	if (size <= HMALLOC_TINY_MAX)
		return (HMALLOC_TINY_ZONE_SIZE);
	else if (size <= HMALLOC_SMALL_MAX)
		return (HMALLOC_SMALL_ZONE_SIZE);
	else
		return (size + sizeof(t_mallocZone) + sizeof(t_mallocBlock));
}

void	*malloc(size_t size)
{
	t_mallocZone	**zoneList;
	t_mallocZone	*newZone;
	t_mallocBlock	*block;
	size_t			alignedSize;

	if (size == 0)
		return (NULL);

	/* Align to 16 bytes */
	alignedSize = (size + HMALLOC_ALIGNMENT - 1) & ~(HMALLOC_ALIGNMENT - 1);

	zoneList = getZoneList(alignedSize);
	block = findFreeBlock(zoneList, alignedSize);

	if (!block)
	{
		newZone = createZone(getZoneSize(alignedSize), alignedSize);
		if (!newZone)
			return (NULL);

		addZoneToList(zoneList, newZone);
		block = newZone->blocks;
	}

	splitBlock(block, alignedSize);
	block->free = 0;
	g_mallocState.totalAlloc += block->size;

	return ((void *)(block + 1));
}

void	free(void *ptr)
{
	t_mallocBlock	*block;

	if (!ptr)
		return;
	block = (t_mallocBlock *)ptr - 1;
	block->free = 1;
	g_mallocState.totalFree += block->size;

	coalesceBlocks(block);
}

void	*realloc(void *ptr, size_t size)
{
	t_mallocBlock	*block;
	void			*newPtr;
	size_t			copySize;

	if (!ptr)
		return (malloc(size));

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	block = (t_mallocBlock *)ptr - 1;
	size = (size + HMALLOC_ALIGNMENT - 1) & ~(HMALLOC_ALIGNMENT - 1);

	/* Try to expand in-place */
	if (block->next && block->next->free &&
		block->size + sizeof(t_mallocBlock) + block->next->size >= size)
	{
		/* Merge with next block */
		block->size += sizeof(t_mallocBlock) + block->next->size;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
		return (ptr);
	}

	/* Otherwise, allocate new block */
	newPtr = malloc(size);
	if (!newPtr)
		return (NULL);

	copySize = (block->size < size) ? block->size : size;
	ft_memcpy(newPtr, ptr, copySize);
	free(ptr);

	return (newPtr);
}
