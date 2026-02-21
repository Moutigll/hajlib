/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gf2nMul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 23:14:46 by moutig            #+#    #+#             */
/*   Updated: 2026/02/20 23:27:34 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/galloisField.h"

uint64_t ft_gf2nMul(uint64_t a, uint64_t b, uint64_t poly, int bits)
{
	uint64_t p = 0;
	uint64_t mask = (bits == 64) ? 0 : ((uint64_t)1 << bits) - 1;
	uint64_t msb_mask = (uint64_t)1 << (bits - 1);
	
	/* Mask inputs to ensure they are within the field */
	a &= mask;
	b &= mask;
	
	while (b) {
		if (b & 1)
			p ^= a;
		b >>= 1;
		
		/* Shift a and reduce if it overflows */
		if (a & msb_mask) {
			a = (a << 1) ^ poly;
		} else {
			a <<= 1;
		}
		
		/* Mask a again to ensure it stays within the field */
		a &= mask;
	}

	return (p & mask);
}
