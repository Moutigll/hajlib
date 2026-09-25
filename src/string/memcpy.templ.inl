/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/**
 * @file memcpy.templ.inl
 * @brief Template for vectorized memcpy implementations.
 * @Created: 2026/09/24 23:34:09 by Moutig
 * @Updated: 2026/09/24 23:59:22 by Moutig
 *
 * This file is included by memcpy.c with different definitions of
 * HAJ_FUNC_NAME, HAJ_VEC_TYPE, HAJ_VEC_SIZE, HAJ_LOAD, HAJ_STORE,
 * and HAJ_TARGET. It implements a vectorized memcpy using the specified vector type and size.
 */

#include <stddef.h>
#include <bits/compiler.h>

#if !defined(HAJ_FUNC_NAME) || !defined(HAJ_VEC_TYPE) || !defined(HAJ_VEC_SIZE) || !defined(HAJ_LOAD) || !defined(HAJ_STORE) || !defined(HAJ_TARGET)
# error "Missing required definitions for memcpy template" /* We keep the defines below to avoid warnings in the IDE. */
typedef __haj_size __HAJ_UNALIGNED_WORD haj_word_t;
# define HAJ_FUNC_NAME		hajMemcpyGeneric
# define HAJ_ATTR_UNUSED	__HAJ_UNUSED
# define HAJ_VEC_TYPE		haj_word_t
# define HAJ_VEC_SIZE		sizeof(haj_word_t)
# define HAJ_LOAD(p)		 (*(const HAJ_VEC_TYPE *)(p))
# define HAJ_STORE(p, v)	(*(HAJ_VEC_TYPE *)(p) = (v))
# define HAJ_TARGET
#endif

HAJ_ATTR_UNUSED
HAJ_TARGET
static void *HAJ_FUNC_NAME(void *__HAJ_RESTRICT dest,
						   const void *__HAJ_RESTRICT src,
						   size_t n)
{
	unsigned char		*d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *)src;

	if (n < HAJ_VEC_SIZE)
	{
		while (n--)
			*d++ = *s++;
		return (dest);
	}

	while (((size_t)d & (HAJ_VEC_SIZE - 1)) && n >= HAJ_VEC_SIZE)
	{
		*d++ = *s++;
		n--;
	}

	while (n >= 4 * HAJ_VEC_SIZE)
	{
		HAJ_VEC_TYPE a = HAJ_LOAD(s + 0 * HAJ_VEC_SIZE);
		HAJ_VEC_TYPE b = HAJ_LOAD(s + 1 * HAJ_VEC_SIZE);
		HAJ_VEC_TYPE c = HAJ_LOAD(s + 2 * HAJ_VEC_SIZE);
		HAJ_VEC_TYPE e = HAJ_LOAD(s + 3 * HAJ_VEC_SIZE);
		HAJ_STORE(d + 0 * HAJ_VEC_SIZE, a);
		HAJ_STORE(d + 1 * HAJ_VEC_SIZE, b);
		HAJ_STORE(d + 2 * HAJ_VEC_SIZE, c);
		HAJ_STORE(d + 3 * HAJ_VEC_SIZE, e);
		s += 4 * HAJ_VEC_SIZE;
		d += 4 * HAJ_VEC_SIZE;
		n -= 4 * HAJ_VEC_SIZE;
	}
	while (n >= HAJ_VEC_SIZE)
	{
		HAJ_VEC_TYPE a = HAJ_LOAD(s);
		HAJ_STORE(d, a);
		s += HAJ_VEC_SIZE;
		d += HAJ_VEC_SIZE;
		n -= HAJ_VEC_SIZE;
	}
	while (n--)
		*d++ = *s++;

	return (dest);
}

# undef HAJ_FUNC_NAME
# undef HAJ_VEC_TYPE
# undef HAJ_VEC_SIZE
# undef HAJ_LOAD
# undef HAJ_STORE
# undef HAJ_TARGET
