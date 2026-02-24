/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gf2nAffine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 23:32:09 by moutig            #+#    #+#             */
/*   Updated: 2026/02/24 17:29:17 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "../../../include/galloisField.h"

/*
 * PRECOMPUTED PARITY TABLE FOR 8-BIT VALUES
 * This lookup table gives parity for any byte in O(1) time.
 * Table[byte] = parity(byte)
 */
static const uint8_t	g_parityTable[256] = {
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /* 0x00-0x0F */
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /* 0x10-0x1F */
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /* 0x20-0x2F */
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /* 0x30-0x3F */
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /* 0x40-0x4F */
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /* 0x50-0x5F */
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /* 0x60-0x6F */
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /* 0x70-0x7F */
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /* 0x80-0x8F */
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /* 0x90-0x9F */
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /* 0xA0-0xAF */
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /* 0xB0-0xBF */
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /* 0xC0-0xCF */
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /* 0xD0-0xDF */
	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /* 0xE0-0xEF */
	0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0  /* 0xF0-0xFF */
};

/**
 * @brief Ultra-fast parity using lookup table
 * 
 * Processes 8 bits at a time using a precomputed table.
 * This is the fastest method for 64-bit values.
 * 
 * @param x 64-bit value
 * @return 1 if odd number of 1 bits, 0 otherwise
 */
static inline uint64_t	__attribute__((unused)) parityFast(uint64_t x)
{
	uint64_t	parity = 0;
	
	/* Process 8 bits at a time using lookup table */
	parity ^= g_parityTable[x & 0xFF];
	parity ^= g_parityTable[(x >> 8) & 0xFF];
	parity ^= g_parityTable[(x >> 16) & 0xFF];
	parity ^= g_parityTable[(x >> 24) & 0xFF];
	parity ^= g_parityTable[(x >> 32) & 0xFF];
	parity ^= g_parityTable[(x >> 40) & 0xFF];
	parity ^= g_parityTable[(x >> 48) & 0xFF];
	parity ^= g_parityTable[(x >> 56) & 0xFF];
	
	return (parity & 1);
}

/**
 * @brief CPU instruction parity (fastest if available)
 * 
 * Uses x86 POPCNT instruction if compiled with -mpopcnt.
 * Falls back to XOR reduce if not available.
 * 
 * @param x 64-bit value
 * @return 1 if odd number of 1 bits, 0 otherwise
 */
static inline uint64_t	parityCpu(uint64_t x)
{
	#if defined(__POPCNT__) && defined(__x86_64__)
		return (__builtin_parityll(x));
	#elif defined(USE_PARITY_TABLE)
		/* Use precomputed table for parity if enabled */
		return (parityFast(x));
	#else
		/* Fallback to XOR reduce */
		x ^= x >> 32;
		x ^= x >> 16;
		x ^= x >> 8;
		x ^= x >> 4;
		x ^= x >> 2;
		x ^= x >> 1;
		return (x & 1);
	#endif
}

/**
 * @brief Apply affine transformation in GF(2^n)
 * 
 * Computes y = (matrix * x) ^ constant where:
 *   - matrix is n x n matrix over GF(2) (one 64-bit mask per output bit)
 *   - x is the input vector (n bits)
 *   - constant is the affine constant (n bits)
 *   - ^ is XOR (addition in GF(2))
 *   - * is matrix multiplication (AND for multiplication, XOR for addition)
 * 
 * Optimizations:
 *   - Uses fastest available parity method based on compile flags
 *   - Pre-computed mask for input validation
 *   - Inline functions for performance
 *   - Branch-free inner loop
 * 
 * @param x Input value (masked to 'bits' internally)
 * @param matrix Array of 'bits' bitmasks (one per output bit)
 * @param constant Affine constant (masked to 'bits' internally)
 * @param bits Field size (1-64)
 * @return Transformed value (masked to 'bits')
 */
uint64_t	ft_gf2nAffine(uint64_t x, const uint64_t *matrix, uint64_t constant, int bits)
{
	uint64_t	mask;
	uint64_t	result;
	int			i;
	
	/* Validate parameters */
	if (bits < 1 || bits > 64 || matrix == NULL)
		return (0);
	
	/* Create mask to keep values within field bounds */
	if (bits == 64)
		mask = ~0ULL;
	else
		mask = ((uint64_t)1 << bits) - 1;
	
	/* Normalize inputs */
	x &= mask;
	constant &= mask;
	
	result = 0;
	
	/* Process each output bit */
	for (i = 0; i < bits; i++)
	{
		/* AND with row mask (matrix multiplication part) */
		uint64_t	product = x & (matrix[i] & mask);
		
		/* Sum in GF(2) = parity of product */
		uint64_t	bit = parityCpu(product);
		
		/* XOR with constant bit */
		bit ^= (constant >> i) & 1;
		
		/* Place bit in result */
		result |= (bit << i);
	}
	
	return (result & mask);
}
