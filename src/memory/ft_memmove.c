/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:29:19 by ele-lean          #+#    #+#             */
/*   Updated: 2024/10/15 18:12:38 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "../../include/memory.h"

void *ft_memmove(void *dstpp, const void *srcpp, size_t len)
{
	uintptr_t dstp = (uintptr_t)dstpp;
	uintptr_t srcp = (uintptr_t)srcpp;
	ptrdiff_t step;

	if (!dstpp && !srcpp)
		return NULL;

	// Determine direction
	if (dstp < srcp)
		step = 1;
	else
	{
		step = -1;
		dstp += len - 1;
		srcp += len - 1;
	}

	// Small copy, just byte by byte
	if (len < sizeof(size_t) * 2)
	{
		BYTE_COPY(dstp, srcp, len, step);
		return dstpp;
	}

	// Align to word
	size_t align_bytes = step > 0 ? (-dstp) % sizeof(size_t) : dstp % sizeof(size_t);
	if (align_bytes)
	{
		size_t n = (align_bytes < len) ? align_bytes : len;
		BYTE_COPY(dstp, srcp, n, step);
		dstp += step * n;
		srcp += step * n;
		len -= n;
	}

	// Page copy
	if (len >= 64)
	{
		size_t pages = len & ~(size_t)63;
		PAGE_COPY(dstp, srcp, pages, step);
		dstp += step * pages;
		srcp += step * pages;
		len -= pages;
	}

	// Word copy
	if (len >= sizeof(size_t))
	{
		size_t words = len & ~(sizeof(size_t)-1);
		WORD_COPY(dstp, srcp, words, step);
		dstp += step * words;
		srcp += step * words;
		len -= words;
	}

	// Remaining bytes
	if (len)
		BYTE_COPY(dstp, srcp, len, step);

	return dstpp;
}
