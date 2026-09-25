/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/**
 * @file memset.c
 * @brief TODO: brief description.
 * @Created: 2026/09/25 20:50:06 by Moutig
 * @Updated: 2026/09/25 21:53:40 by Moutig
 *
 * TODO: description.
 */

#include <string.h>
#include <bits/cpu.h>

/* Splat helper for the generic implementation. */
static inline __haj_size hajMemsetSplat(unsigned char v)
{
	__haj_size w = (__haj_size)v;
	w |= w << 8;
	w |= w << 16;
# if __HAJ_WORDSIZE == 64
	w |= w << 32;
# endif
	return (w);
}

# define HAJ_PREFIX	hajMemset
# include "../impl/memsetImpl.h"
# undef HAJ_PREFIX

/* ----- Dispatcher ----- */

#if defined(__ELF__) && (defined(__x86_64__) || defined(_M_X64))



static void *memsetSelectImpl(void)
{
	if (hajCpuHasAvx512())
		return ((void *)hajMemsetAvx512);
	if (hajCpuHasAvx2())
		return ((void *)hajMemsetAvx2);
	return ((void *)hajMemsetSse2);
}

void *memset(void *dest, int c, size_t n)
{
	static void *(*memsetFunc)(void *, int, size_t) = NULL;

	if (memsetFunc == NULL)
		memsetFunc = (void *(*)(void *, int, size_t))memsetSelectImpl();

	return (memsetFunc(dest, c, n));
}

#elif defined(__aarch64__)

void *memset(void *dest, int c, size_t n)
	__HAJ_ALIAS(hajMemsetNeon);

#else

# if defined(__x86_64__) || defined(_M_X64)
#  define HAJ_MEMSET_IMPL hajMemsetSse2
# elif defined(__aarch64__)
#  define HAJ_MEMSET_IMPL hajMemsetNeon
# else
#  define HAJ_MEMSET_IMPL hajMemsetGeneric
# endif

void *memset(void *dest, int c, size_t n)
{
	return (HAJ_MEMSET_IMPL(dest, c, n));
}

#endif
