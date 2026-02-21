/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gf2nInv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 23:15:51 by moutig            #+#    #+#             */
/*   Updated: 2026/02/20 23:27:04 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/galloisField.h"

uint64_t ft_gf2nInv(uint64_t x, uint64_t poly, int bits)
{
	if (x == 0) return 0;
	
	/* Optimisation for small fields (e.g. GF(2^8)) using a precomputed table */
	if (bits <= 8) {
		static uint64_t cache[256] = {0};
		static uint64_t cached_poly = 0;
		static int cached_bits = 0;
		
		/* Recompute the cache if the polynomial or bit size changes */
		if (cached_poly != poly || cached_bits != bits) {
			for (int i = 1; i < (1 << bits); i++) {
				uint64_t exp = (1ULL << bits) - 2;
				cache[i] = ft_gf2nPow(i, exp, poly, bits);
			}
			cached_poly = poly;
			cached_bits = bits;
		}
		return cache[x];
	}
	
	/* For larger fields, use exponentiation by squaring to compute the inverse:
	 * x^{-1} = x^{2^n - 2} mod poly
	 * This is efficient and works for any field size.
	 */
	uint64_t exp = (1ULL << bits) - 2;
	return ft_gf2nPow(x, exp, poly, bits);
}
