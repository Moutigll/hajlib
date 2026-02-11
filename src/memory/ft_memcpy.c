#include <stddef.h>
#include <stdint.h>

#include "../../include/memory.h"


void *ft_memcpy(void *dstpp, const void *srcpp, size_t len)
{
	uintptr_t	dstp = (uintptr_t)dstpp;
	uintptr_t	srcp = (uintptr_t)srcpp;

	/* If the length is small, just copy byte by byte */
	if (len < sizeof(size_t) * 2)
	{
		BYTE_COPY(dstpp, srcpp, len, 1);
		return dstpp;
	}

	/* Align the destination pointer to a word boundary */
	size_t align_bytes = (-dstp) % sizeof(size_t);
	if (align_bytes)
	{
		BYTE_COPY((void*)dstp, (void*)srcp, align_bytes, 1);
		dstp += align_bytes;
		srcp += align_bytes;
		len -= align_bytes;
	}

	/* If the length is large, copy in page-sized chunks */
	if (len >= 64)
	{
		PAGE_COPY((void*)dstp, (void*)srcp, len & ~(size_t)63, 1);
		size_t copied = len & ~(size_t)63;
		dstp += copied;
		srcp += copied;
		len -= copied;
	}

	/* If we still have enough data, copy in word-sized chunks */
	if (len >= sizeof(size_t))
	{
		WORD_COPY((void*)dstp, (void*)srcp, len & ~(sizeof(size_t)-1), 1);
		size_t copied = len & ~(sizeof(size_t)-1);
		dstp += copied;
		srcp += copied;
		len -= copied;
	}

	/* Copy any remaining bytes */
	if (len)
		BYTE_COPY((void*)dstp, (void*)srcp, len, 1);

	return (dstpp);
}
