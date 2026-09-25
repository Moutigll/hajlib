/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/**
 * @file memcpy.c
 * @brief C standard memcpy implementation with vectorization.
 * @Created: 2026/09/24 23:08:35 by Moutig
 * @Updated: 2026/09/25 02:32:50 by Moutig
 *
 * This file implements the C standard memcpy function, which copies
 * n bytes from the source buffer to the destination buffer. It uses
 * vectorized implementations for x86_64 (SSE2, AVX2, AVX-512) and
 * aarch64 (NEON) when available, falling back to a generic implementation otherwise.
 *
 * @TODO: implement Erms optimization for x86_64 if available with
 *  per CPU thresholds to optimize big copies outside of cache.
 */

#include <string.h>
#include <bits/cpu.h>


/* Generic word type for memcpy */
typedef __haj_size __HAJ_UNALIGNED_WORD haj_word_t;


# define HAJ_FUNC_NAME		hajMemcpyGeneric
# define HAJ_ATTR_UNUSED	__HAJ_UNUSED
# define HAJ_VEC_TYPE		haj_word_t
# define HAJ_VEC_SIZE		sizeof(haj_word_t)
# define HAJ_LOAD(p)		 (*(const HAJ_VEC_TYPE *)(p))
# define HAJ_STORE(p, v)	(*(HAJ_VEC_TYPE *)(p) = (v))
# define HAJ_TARGET

#include "memcpy.templ.inl"

/* ----- Vectorized implementations (x86_64, aarch64) ----- */

#if defined(__x86_64__) || defined(_M_X64) /* x86_64 : SSE2, AVX2, AVX-512 (optional) */

# include <emmintrin.h>	/* SSE2 */
# include <immintrin.h>	/* AVX, AVX2, AVX-512 */

/* ---- SSE2 (baseline x86_64) ---- */

# define HAJ_FUNC_NAME		hajMemcpySse2
# define HAJ_VEC_TYPE		__m128i
# define HAJ_VEC_SIZE		16
# define HAJ_LOAD(p)		_mm_loadu_si128((const __m128i *)(p))
# define HAJ_STORE(p, v)	_mm_store_si128((__m128i *)(p), (v))
# define HAJ_TARGET	 		__HAJ_TARGET("sse2")

# include "memcpy.templ.inl"

/* ---- AVX2 ---- */

# define HAJ_FUNC_NAME		hajMemcpyAvx2
# define HAJ_VEC_TYPE		__m256i
# define HAJ_VEC_SIZE		32
# define HAJ_LOAD(p)		_mm256_loadu_si256((const __m256i *)(p))
# define HAJ_STORE(p, v)	_mm256_store_si256((__m256i *)(p), (v))
# define HAJ_TARGET			__HAJ_TARGET("avx2")

# include "memcpy.templ.inl"

/* ---- AVX-512 (optionnel) ---- */

# define HAJ_FUNC_NAME		hajMemcpyAvx512
# define HAJ_VEC_TYPE		__m512i
# define HAJ_VEC_SIZE		64
# define HAJ_LOAD(p)		_mm512_loadu_si512((const void *)(p))
# define HAJ_STORE(p, v)	_mm512_storeu_si512((void *)(p), (v))
# define HAJ_TARGET	 		__HAJ_TARGET("avx512f,avx512bw,avx512vl")

# include "memcpy.templ.inl"

#endif /* x86_64 */


/* ----- aarch64 : NEON (baseline) ---- */

#if defined(__aarch64__)

# include <arm_neon.h>

# define HAJ_FUNC_NAME		hajMemcpyNeon
# define HAJ_VEC_TYPE		uint8x16_t
# define HAJ_VEC_SIZE		16
# define HAJ_LOAD(p)		vld1q_u8((const uint8_t *)(p))
# define HAJ_STORE(p, v)	vst1q_u8((uint8_t *)(p), (v))
# define HAJ_TARGET

# include "memcpy.templ.inl"

#endif /* aarch64 */


/* ----- Resolver and dispatch ----- */

#if defined(__ELF__) && (defined(__x86_64__) || defined(_M_X64))
/* Dispatcher: choose the best implementation once, cache it. */
static void *(*g_memcpyImpl)(void *, const void *, size_t) = NULL;


static void *memcpySelectImpl(void)
{
	if (hajCpuHasAvx512())
		return ((void *)hajMemcpyAvx512);
	if (hajCpuHasAvx2())
		return ((void *)hajMemcpyAvx2);
	return ((void *)hajMemcpySse2);
}

void *memcpy(void *__HAJ_RESTRICT dest,
			 const void *__HAJ_RESTRICT src,
			 size_t n)
{
	if (g_memcpyImpl == NULL)
		g_memcpyImpl = (void *(*)(void *, const void *, size_t))memcpySelectImpl();
	return (g_memcpyImpl(dest, src, n));
}
#elif defined(__aarch64__)
/* aarch64 : NEON is baseline, so we can directly alias memcpy to the NEON implementation. */

void *memcpy(void		*__HAJ_RESTRICT dest,
			 const void	*__HAJ_RESTRICT src,
			 size_t		n)
	__HAJ_ALIAS(hajMemcpyNeon);

#else
/* Fallback : dispatch compile-time */

# if defined(__x86_64__) || defined(_M_X64)
#  define HAJ_MEMCPY_IMPL hajMemcpySse2
# elif defined(__aarch64__)
#  define HAJ_MEMCPY_IMPL hajMemcpyNeon
# else
#  define HAJ_MEMCPY_IMPL hajMemcpyGeneric
# endif

void *memcpy(void *__HAJ_RESTRICT dest,
			 const void *__HAJ_RESTRICT src,
			 size_t n)
{
	return (HAJ_MEMCPY_IMPL(dest, src, n));
}
#endif
