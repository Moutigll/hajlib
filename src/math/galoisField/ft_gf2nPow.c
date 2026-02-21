/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gfnPow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 23:24:53 by moutig            #+#    #+#             */
/*   Updated: 2026/02/20 23:27:44 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/galloisField.h"

uint64_t ft_gf2nPow(uint64_t base, uint64_t exp, uint64_t poly, int bits)
{
	if (bits < 1 || bits > 64 || poly == 0)
		return (0);
	
	if (exp == 0)
		return (1);
	
	if (base == 0)
		return (0);
	
	/* Mask to ensure it fits within the field size */
	uint64_t mask = (bits == 64) ? ~0ULL : ((uint64_t)1 << bits) - 1;
	base &= mask;
	
	uint64_t result = 1;
	uint64_t current_power = base;
	uint64_t remaining_exp = exp;
	
	/* Exponentiation by squaring */
	while (remaining_exp > 0) {
		/* If the least significant bit of the exponent is 1, multiply the result by the current power */
		if (remaining_exp & 1) {
			result = ft_gf2nMul(result, current_power, poly, bits);
		}
		
		/* Square the current power for the next bit */
		current_power = ft_gf2nMul(current_power, current_power, poly, bits);
		remaining_exp >>= 1; /* Shift the exponent right by 1 bit to process the next bit */
	}
	
	return (result & mask);
}
