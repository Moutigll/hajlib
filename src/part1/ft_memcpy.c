#include <stdint.h>

#include "../../include/libft.h"

/**
 * @brief Copies `n` bytes from memory area `src` to memory area `dest`.
 * The memory areas must not overlap. Use `ft_memmove` if they do.
 */
#define BYTE_COPY_FWD(d,s,len)						\
	do {											\
		size_t _i;									\
		unsigned char *_d = (unsigned char*)(d);	\
		unsigned char *_s = (unsigned char*)(s);	\
		for (_i = 0; _i < (len); _i++)				\
			_d[_i] = _s[_i];						\
	} while(0)

/**
 * @brief Copies `n` bytes from memory area `src` to memory area `dest` in word-sized chunks.
 * The memory areas must not overlap. Use `ft_memmove` if they do.
 */
#define WORD_COPY_FWD(d,s,len)					\
	do {										\
		size_t _i, _n = (len)/sizeof(size_t);	\
		size_t *_d = (size_t*)(d);				\
		size_t *_s = (size_t*)(s);				\
		size_t _unroll = _n / 8;				\
		for (_i = 0; _i < _unroll; _i++) {		\
			_d[0] = _s[0];						\
			_d[1] = _s[1];						\
			_d[2] = _s[2];						\
			_d[3] = _s[3];						\
			_d[4] = _s[4];						\
			_d[5] = _s[5];						\
			_d[6] = _s[6];						\
			_d[7] = _s[7];						\
			_d += 8; _s += 8;					\
		}										\
		for (_i = 0; _i < (_n % 8); _i++)		\
			_d[_i] = _s[_i];					\
	} while(0)

/**
 * @brief Copies `n` bytes from memory area `src` to memory area `dest` in page-sized chunks.
 * The memory areas must not overlap. Use `ft_memmove` if they do.
 */
#define PAGE_COPY_FWD(d,s,len)				\
	do {									\
		size_t _i, _n = (len)/64;			\
		size_t *_d = (size_t*)(d);			\
		size_t *_s = (size_t*)(s);			\
		for (_i = 0; _i < _n; _i++) {		\
			_d[0] = _s[0]; _d[1] = _s[1];	\
			_d[2] = _s[2]; _d[3] = _s[3];	\
			_d[4] = _s[4]; _d[5] = _s[5];	\
			_d[6] = _s[6]; _d[7] = _s[7];	\
			_d += 8; _s += 8;				\
		}									\
	} while(0)


void *ft_memcpy(void *dstpp, const void *srcpp, size_t len)
{
	uintptr_t dstp = (uintptr_t)dstpp;
	uintptr_t srcp = (uintptr_t)srcpp;

	/* If the length is small, just copy byte by byte */
	if (len < sizeof(size_t) * 2)
	{
		BYTE_COPY_FWD(dstpp, srcpp, len);
		return dstpp;
	}

	/* Align the destination pointer to a word boundary */
	size_t align_bytes = (-dstp) % sizeof(size_t);
	if (align_bytes)
	{
		BYTE_COPY_FWD(dstpp, srcpp, align_bytes);
		dstp += align_bytes;
		srcp += align_bytes;
		len -= align_bytes;
	}

	/* If the length is large, copy in page-sized chunks */
	if (len >= 64)
	{
		PAGE_COPY_FWD((void*)dstp, (void*)srcp, len & ~(size_t)63);
		size_t copied = len & ~(size_t)63;
		dstp += copied;
		srcp += copied;
		len -= copied;
	}

	/* If we still have enough data, copy in word-sized chunks */
	if (len >= sizeof(size_t))
	{
		WORD_COPY_FWD((void*)dstp, (void*)srcp, len & ~(sizeof(size_t)-1));
		size_t copied = len & ~(sizeof(size_t)-1);
		dstp += copied;
		srcp += copied;
		len -= copied;
	}

	/* Copy any remaining bytes */
	if (len)
		BYTE_COPY_FWD((void*)dstp, (void*)srcp, len);

	return (dstpp);
}
