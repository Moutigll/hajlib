/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:32:23 by ele-lean          #+#    #+#             */
/*   Updated: 2024/10/14 15:51:47 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "../../include/memory.h"

#define BYTE_SET(d, c, len)					\
	do {										\
		size_t _i;									\
		unsigned char *_d = (unsigned char*)(d);	\
		for (_i = 0; _i < (len); _i++)				\
			_d[_i] = (unsigned char)(c);			\
	} while(0)

#define WORD_SET(d, pattern, len)				\
	do {										\
		size_t _i, _n = (len)/sizeof(size_t);	\
		size_t *_d = (size_t*)(d);				\
		for (_i = 0; _i < _n; _i++)		{										\
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

	/* First align the pointer to a word boundary */
	size_t align = (-ptr) % sizeof(size_t);
	if (align && n >= align)
	{
		BYTE_SET((void*)ptr, byte, align);
		ptr += align;
		n -= align;
	}

	/* Then set in word-sized chunks */
	if (n >= sizeof(size_t))
	{
		size_t pattern = 0;
		for (size_t i = 0; i < sizeof(size_t); i++)
			pattern |= (size_t)byte << (i * 8);
		size_t len = n & ~(sizeof(size_t)-1);
		WORD_SET((void*)ptr, pattern, len);
		ptr += len;
		n -= len;
	}

	/* Finally set any remaining bytes */
	if (n)
		BYTE_SET((void*)ptr, byte, n);

	return (s);
}
