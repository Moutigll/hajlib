/*
 * Thread-local cache for small allocations.
 *
 * This file defines the lightweight allocator cache used by the malloc
 * implementation. The goal of the tcache is to avoid repeatedly asking the
 * global allocator for small blocks by keeping recently freed or reusable
 * memory in a per-thread structure. This reduces locking and contention, and it
 * helps small allocations perform efficiently when they are created and freed
 * often by the same thread.
 *
 * The cache is organized as a fixed number of bins. Each bin corresponds to a
 * size class, and the size of each block in that bin is rounded up to a
 * multiple of TCACHE_ALIGNMENT. For example, all allocations in a given bin are
 * treated as the same size and stored as linked-list nodes. A bin contains a
 * pointer to its head entry and a count of how many entries are currently cached.
 *
 * When memory is freed, the allocator can place the block into the current
 * thread's tcache if it fits the size class and the bin is not full. When a new
 * allocation is requested, the allocator checks the matching bin first. If a
 * free block is available, it is reused immediately without touching the global
 * heap. If the bin is empty or the cache is full, allocation falls back to the
 * shared allocator logic.
 *
 * This design keeps the cache compact and fast: each bin is just a linked list
 * of nodes, and each node is only a pointer to the next block. The structure is
 * intentionally thread-local so that different threads do not compete for the
 * same cached blocks, which is especially useful in multithreaded programs.
 */

#ifndef TCACHE_H
#define TCACHE_H

#include "malloc.h"

# define TCACHE_MAX_SIZE	8192
# define TCACHE_ALIGNMENT	16
# define TCACHE_NUM_BINS	(TCACHE_MAX_SIZE / TCACHE_ALIGNMENT)  /* 128 */
# define TCACHE_MAX_PER_BIN	128	/* Maximum number of cached blocks per bin */

/*
 * How many higher bins to scan when the exact bin is empty. Because
 * splitBlock() may leave a block slightly larger than requested (when
 * the remainder is smaller than a header), a block freed for size N can
 * end up in bin N+1, N+2, ... up to N+3 (48 bytes / 16 = 3). We scan
 * that many extra bins to guarantee a hit.
 */
# define TCACHE_SEARCH_LIMIT	4

/**
 * @struct s_tcacheEntry
 * @brief Represents an entry in the tcache.
 * 
 * This structure is used to represent a single entry in the tcache, which is a
 * thread-local cache for small memory allocations. Each entry points to the next
 * entry in the same bin.
 * 
 * @member next Pointer to the next entry in the same bin.
 */
typedef struct s_tcacheEntry {
	struct s_tcacheEntry	*next;
} t_tcacheEntry;

/**
 * @struct s_tcache
 * @brief Represents the thread-local cache (tcache) for small memory allocations.
 * 
 * This structure is used to manage the tcache, which is a thread-local cache for
 * small memory allocations. It contains an array of bins, each of which holds a
 * linked list of free memory blocks of a specific size.
 * 
 * @member bins An array of pointers to the head of the linked list for each bin.
 * @member counts An array of counts indicating the number of free blocks in each bin.
 */
typedef struct s_tcache {
	t_tcacheEntry	*bins[TCACHE_NUM_BINS];
	uint16_t		counts[TCACHE_NUM_BINS];
} t_tcache;



/**
 * @brief Retrieves the thread-local tcache for the current thread.
 * 
 * This function returns a pointer to the thread-local tcache structure for the
 * current thread. The tcache is used to cache small memory allocations and
 * reduce contention on the global heap allocator.
 * 
 * @return A pointer to the thread-local tcache for the current thread.
 */
t_tcache		*tcacheGet(void);

/**
 * @brief Flushes the thread-local tcache for the current thread.
 * 
 * This function clears the contents of the thread-local tcache, releasing any
 * cached memory blocks back to the global heap allocator. It is typically called
 * when a thread is exiting or when the tcache needs to be reset.
 * 
 * @param tc A pointer to the thread-local tcache to flush.
 */
void			tcacheFlush(t_tcache *tc);



static inline int tcacheSizeToBin(size_t size)
{
	if (size == 0 || size > TCACHE_MAX_SIZE)
		return (-1);
	return ((int)((size + TCACHE_ALIGNMENT - 1) / TCACHE_ALIGNMENT) - 1);
}

static inline size_t tcacheBinToSize(int bin)
{
	return ((size_t)(bin + 1) * TCACHE_ALIGNMENT);
}
#endif
