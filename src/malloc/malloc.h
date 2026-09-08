#ifndef HMALLOC_PRIVATE_H
# define HMALLOC_PRIVATE_H

#include <pthread.h>
#include <unistd.h>

# include "../../include/hmalloc.h"

# define HMALLOC_MIN_BLOCKS			100
# define HMALLOC_TINY_ZONE_SIZE		(8 * getpagesize())		/* 8 pages ~ 32 Ko */
# define HMALLOC_SMALL_ZONE_SIZE	(32 * getpagesize())	/* 32 pages ~ 128 Ko */

/**
 * @struct s_mallocState
 * @brief Represents the state of the heap memory allocator.
 * 
 * This structure maintains the overall state of the custom malloc implementation,
 * including pointers to different memory zones, a mutex for thread safety, and
 * statistics about total allocated and freed memory.
 * 
 * @member tinyZones Pointer to the linked list of tiny memory zones.
 * @member smallZones Pointer to the linked list of small memory zones.
 * @member largeZones Pointer to the linked list of large memory zones.
 * @member mutex A mutex for synchronizing access to the allocator state in multithreaded environments.
 * @member totalAlloc The total amount of memory allocated by the allocator in bytes.
 * @member totalFree The total amount of memory freed by the allocator in bytes.
 */
typedef struct s_mallocState {
	t_mallocZone	*tinyZones;
	t_mallocZone	*smallZones;
	t_mallocZone	*largeZones;
	pthread_mutex_t	mutex;
	size_t			totalAlloc;
	size_t			totalFree;
}	t_mallocState;

/**
 * @brief Global state of the heap memory allocator.
 * 
 * This variable holds the global state of the custom malloc implementation,
 * including pointers to different memory zones, a mutex for thread safety, and
 * statistics about total allocated and freed memory. It is used internally by
 * the allocator functions to manage memory allocations and deallocations.
 */
extern t_mallocState	g_mallocState;

/**
 * @brief Creates a new memory zone of the specified size.
 * 
 * This function allocates a new memory zone of the given size and initializes
 * its metadata. It returns a pointer to the newly created memory zone.
 * 
 * @param zoneSize The size of the memory zone to create in bytes.
 * @param blockSize The size of individual blocks within the zone in bytes.
 * @return A pointer to the newly created memory zone, or NULL if allocation fails.
 */
t_mallocZone	*createZone(size_t zoneSize, size_t blockSize);

/**
 * @brief Finds a free memory block of the specified size within the given zone list.
 * 
 * This function searches through the linked list of memory zones to find a free
 * memory block that can accommodate the requested size. If a suitable block is
 * found, it returns a pointer to that block; otherwise, it returns NULL.
 * 
 * @param zoneList A pointer to the head of the linked list of memory zones.
 * @param size The size of the memory block to find in bytes.
 * @return A pointer to a free memory block of the requested size, or NULL if none is found.
 */
t_mallocBlock	*findFreeBlock(t_mallocZone **zoneList, size_t size);

/**
 * @brief Splits a memory block into two smaller blocks.
 * 
 * This function splits the given memory block into two smaller blocks if the
 * block is large enough to accommodate the requested size. The original block
 * is resized, and a new free block is created for the remaining space.
 * 
 * @param block Pointer to the memory block to split.
 * @param size The size of the first block after splitting in bytes.
 */
void			splitBlock(t_mallocBlock *block, size_t size);

/**
 * @brief Coalesces adjacent free memory blocks into a single larger block.
 * 
 * This function merges adjacent free memory blocks into a single larger block
 * to reduce fragmentation and improve memory utilization. It updates the linked
 * list of blocks accordingly.
 * 
 * @param block Pointer to the memory block to coalesce with its neighbors.
 */
void			coalesceBlocks(t_mallocBlock *block);

/**
 * @brief Adds a new memory zone to the linked list of zones.
 * 
 * This function adds the specified memory zone to the linked list of zones,
 * maintaining the order of zones based on their sizes. It updates the pointers
 * in the linked list accordingly.
 * 
 * @param list A pointer to the head of the linked list of memory zones.
 * @param zone Pointer to the memory zone to add to the list.
 */
void			addZoneToList(t_mallocZone **list, t_mallocZone *zone);

#endif
