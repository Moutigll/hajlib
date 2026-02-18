#ifndef HAJLIB_MEMORY_H
#define HAJLIB_MEMORY_H

/**
 * To use these macros effectively, ensure that you compile with -O3
 * and that the source and destination pointers are properly aligned for the chunk size.
 * The compiler will optimize the loops and unrolling, resulting in very fast memory copying for large buffers.
 */

#define BYTE_COPY(d, s, len, step)					\
	do {											\
		size_t _i;									\
		unsigned char *_d = (unsigned char*)(d);	\
		unsigned char *_s = (unsigned char*)(s);	\
		for (_i = 0; _i < (len); _i++)				\
		{											\
			*_d = *_s;								\
			_d += (step);							\
			_s += (step);							\
		}											\
	} while(0)

#define WORD_COPY(d, s, len, step)				\
	do {										\
		size_t _i, _n = (len)/sizeof(size_t);	\
		size_t *_d = (size_t*)(d);				\
		size_t *_s = (size_t*)(s);				\
		for (_i = 0; _i < _n; _i++)				\
		{										\
			*_d = *_s;							\
			_d += (step);						\
			_s += (step);						\
		}										\
	} while(0)

#define PAGE_COPY(d, s, len, step)			\
	do {									\
		size_t _i, _n = (len)/64;			\
		size_t *_d = (size_t*)(d);			\
		size_t *_s = (size_t*)(s);			\
		for (_i = 0; _i < _n; _i++)			\
		{									\
			_d[0] = _s[0]; _d[1] = _s[1];	\
			_d[2] = _s[2]; _d[3] = _s[3];	\
			_d[4] = _s[4]; _d[5] = _s[5];	\
			_d[6] = _s[6]; _d[7] = _s[7];	\
			_d += (8*(step));				\
			_s += (8*(step));				\
		}									\
	} while(0)

#include <stddef.h>

/**
 * @brief Sets the first n bytes of the memory area pointed to by s to zero.
 * @param s - pointer to the memory area to be filled with zeros
 * @param n - number of bytes to be set to zero
 * @return a pointer to the memory area s
 */
void	*ft_bzero(void *s, size_t n);

/**
 * @brief Allocates memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.
 * The memory is set to zero.
 * @param nmemb - number of elements to allocate
 * @param size - size of each element in bytes
 * @return a pointer to the allocated memory, or NULL if the allocation fails
 */
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Copies n bytes from memory area src to memory area dest. The memory areas must not overlap.
 * @param dest - pointer to the destination memory area
 * @param src - pointer to the source memory area
 * @param n - number of bytes to copy
 * @return a pointer to the destination memory area dest
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares the first n bytes of the memory areas s1 and s2.
 * @param s1 - pointer to the first memory area
 * @param s2 - pointer to the second memory area
 * @param n - number of bytes to compare
 * @return an integer less than, equal to, or greater than zero if the first n bytes of s1 is found, respectively, to be less than, to match, or be greater than the first n bytes of s2
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);


/**
 * @brief Copies n bytes from memory area src to memory area dest. The memory areas must not overlap.
 * @param dest - pointer to the destination memory area
 * @param src - pointer to the source memory area
 * @param n - number of bytes to copy
 * @return a pointer to the destination memory area dest
 */
void	*ft_memcpy(void *dstpp, const void *srcpp, size_t len);

/**
 * @brief Copies n bytes from memory area src to memory area dest. The memory areas may overlap.
 * @param dest - pointer to the destination memory area
 * @param src - pointer to the source memory area
 * @param n - number of bytes to copy
 * @return a pointer to the destination memory area dest
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Fills the first n bytes of the memory area pointed to by s with the constant byte c.
 * @param s - pointer to the memory area to be filled
 * @param c - byte to fill the memory area with
 * @param n - number of bytes to fill
 * @return a pointer to the memory area s
 */
void	*ft_memset(void *s, int c, size_t n);

#endif /* HAJLIB_MEMORY_H */
