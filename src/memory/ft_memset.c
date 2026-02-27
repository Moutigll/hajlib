/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:32:23 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/27 20:39:22 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "../../include/hmemory.h"

#define BYTE_SET(d, c, len)						\
	do {										\
		size_t _i;								\
		unsigned char *_d = (unsigned char*)(d);\
		for (_i = 0; _i < (len); _i++)			\
			_d[_i] = (unsigned char)(c);		\
	} while(0)

#define WORD_SET(d, pattern, len)				\
	do {										\
		size_t _i, _n = (len)/sizeof(size_t);	\
		size_t *_d = (size_t*)(d);				\
		for (_i = 0; _i < _n; _i++)				\
			*_d++ = (pattern);					\
	} while(0)

#define PAGE_SET(d, pattern, len)				\
	do {										\
		size_t _i, _n = (len)/64;				\
		size_t *_d = (size_t*)(d);				\
		for (_i = 0; _i < _n; _i++)				\
		{										\
			_d[0] = (pattern);					\
			_d[1] = (pattern);					\
			_d[2] = (pattern);					\
			_d[3] = (pattern);					\
			_d[4] = (pattern);					\
			_d[5] = (pattern);					\
			_d[6] = (pattern);					\
			_d[7] = (pattern);					\
			_d += 8;							\
		}										\
	} while(0)

void	*ft_memset(void *s, int c, size_t n)
{
	uintptr_t		ptr = (uintptr_t)s;
	unsigned char	byte = (unsigned char)c;

	/* For small sizes, just set byte by byte */
	if (n < sizeof(size_t) * 2)
	{
		BYTE_SET(s, byte, n);
		return (s);
	}

	/* Align the pointer to a word boundary */
	size_t align_bytes = (-ptr) % sizeof(size_t);
	if (align_bytes)
	{
		BYTE_SET((void*)ptr, byte, align_bytes);
		ptr += align_bytes;
		n -= align_bytes;
	}

	/* Create a word-sized pattern of the byte */
	size_t pattern = 0;
	for (size_t i = 0; i < sizeof(size_t); i++)
		pattern |= (size_t)byte << (i * 8);

	/* If the size is large, set in page-sized chunks */
	if (n >= 64)
	{
		size_t page_len = n & ~(size_t)63;
		PAGE_SET((void*)ptr, pattern, page_len);
		ptr += page_len;
		n -= page_len;
	}

	/* Copy in word-sized chunks */
	if (n >= sizeof(size_t))
	{
		size_t word_len = n & ~(sizeof(size_t) - 1);
		WORD_SET((void*)ptr, pattern, word_len);
		ptr += word_len;
		n -= word_len;
	}

	/* Set any remaining bytes */
	if (n)
		BYTE_SET((void*)ptr, byte, n);

	return (s);
}
