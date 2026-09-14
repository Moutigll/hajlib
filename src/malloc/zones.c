#include "malloc.h"
#include "mallocos.h"

t_mallocZone	*createZone(size_t zoneSize, size_t blockSize)
{
	t_mallocZone	*zone;
	t_mallocBlock	*block;
	t_mallocBlock	*prev;
	size_t			blockCount;
	size_t			i;
	size_t			offset;
	size_t			blockTotal;

	zone = hmallocMap(zoneSize);

	zone->size = zoneSize;
	zone->blocks = NULL;
	zone->next = NULL;

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
		block->prev = prev;
		block->next = NULL;

		if (prev)
			prev->next = block;
		else
			zone->blocks = block;	/* lowest-address block is the head */

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

t_mallocBlock	*findFreeBlock(t_mallocZone **zoneList, size_t size)
{
	t_mallocZone	*zone;
	t_mallocBlock	*block;

	zone = *zoneList;
	while (zone)
	{
		block = zone->blocks;
		while (block)
		{
			if (block->free && block->size >= size)
				return (block);
			block = block->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

void	splitBlock(t_mallocBlock *block, size_t size)
{
	t_mallocBlock	*newBlock;

	if (!block || block->size <= size + sizeof(t_mallocBlock))
		return;

	newBlock = (t_mallocBlock *)((char *)(block + 1) + size);
	newBlock->size = block->size - size - sizeof(t_mallocBlock);
	newBlock->next = block->next;
	newBlock->prev = block;
	newBlock->free = 1;

	block->size = size;
	block->next = newBlock;
	if (newBlock->next)
		newBlock->next->prev = newBlock;

}

void coalesceBlocks(t_mallocBlock *block) {
	__attribute__((unused)) t_mallocBlock *final = block;
	if (!block) return;

	if (block->next && block->next->free) {
		t_mallocBlock *oldNext = block->next;
		block->size += sizeof(t_mallocBlock) + oldNext->size;
		block->next = oldNext->next;
		if (block->next) block->next->prev = block;
		oldNext->prev = NULL;
		oldNext->next = NULL;
		oldNext->size = 0;
		final = block;
	}

	if (block->prev && block->prev->free) {
		t_mallocBlock *oldBlock = block;
		block->prev->size += sizeof(t_mallocBlock) + oldBlock->size;
		block->prev->next = oldBlock->next;
		if (oldBlock->next) oldBlock->next->prev = block->prev;
		oldBlock->prev = NULL;
		oldBlock->next = NULL;
		oldBlock->size = 0;
		final = block->prev;
	}

}
