#ifndef HMALLOC_H
# define HMALLOC_H

# include <stddef.h>

# define HMALLOC_TINY_MAX		128
# define HMALLOC_SMALL_MAX		1024
# define HMALLOC_ALIGNMENT		16	/* Align adresses for fast access */

/**
 * @struct s_mallocBlock
 * @brief Represents a memory allocation block in the heap memory allocator.
 * 
 * This structure is used to manage individual memory blocks allocated by the
 * custom malloc implementation. It maintains metadata for tracking allocated
 * and freed memory regions.
 * 
 * @member size The size of the allocated memory block in bytes.
 * @member next Pointer to the next memory block in the linked list.
 * @member prev Pointer to the previous memory block in the linked list.
 * @member free Flag indicating whether the block is free (1) or allocated (0).
 */
typedef struct s_mallocBlock {
	size_t					size;
	struct s_mallocBlock	*next;
	struct s_mallocBlock	*prev;
	int						free;
}	t_mallocBlock;

/**
 * @struct s_mallocZone
 * @brief Represents a memory zone in the heap memory allocator.
 * 
 * This structure is used to manage a collection of memory blocks within a
 * specific memory zone. It maintains metadata for tracking the size of the
 * zone and the linked list of allocated blocks.
 * 
 * @member size The total size of the memory zone in bytes.
 * @member blocks Pointer to the first memory block in the linked list of blocks.
 * @member next Pointer to the next memory zone in the linked list.
 */
typedef struct s_mallocZone {
	size_t				size;
	t_mallocBlock		*blocks;
	struct s_mallocZone	*next;
}	t_mallocZone;

/**
 * @brief Allocates a block of memory of the specified size.
 * 
 * This function allocates a block of memory of the given size and returns a
 * pointer to the beginning of the allocated memory. If the allocation fails,
 * it returns NULL.
 * 
 * @param size The size of the memory block to allocate in bytes.
 * @return A pointer to the allocated memory block, or NULL if allocation fails.
 */
void	*malloc(size_t size);

/**
 * @brief Frees a previously allocated block of memory.
 * 
 * This function frees the memory block pointed to by ptr, which must have been
 * returned by a previous call to malloc, calloc, or realloc. If ptr is NULL,
 * no operation is performed.
 * 
 * @param ptr Pointer to the memory block to free.
 */
void	free(void *ptr);

/**
 * @brief Reallocates a block of memory to a new size.
 * 
 * This function changes the size of the memory block pointed to by ptr to the
 * specified size. The contents will be unchanged up to the minimum of the old
 * and new sizes. If the new size is larger, the added memory will not be
 * initialized. If ptr is NULL, this function behaves like malloc(size).
 * If size is zero and ptr is not NULL, this function behaves like free(ptr).
 * 
 * @param ptr Pointer to the memory block to reallocate.
 * @param size The new size for the memory block in bytes.
 * @return A pointer to the reallocated memory block, or NULL if reallocation fails.
 */
void	*realloc(void *ptr, size_t size);

/**
 * @brief Displays the current state of allocated memory blocks.
 * 
 * This function prints information about the currently allocated memory blocks,
 * including their sizes and addresses. It is useful for debugging and monitoring
 * memory usage in the custom malloc implementation.
 */
void	show_alloc_mem(void);

#endif
