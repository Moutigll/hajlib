/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 19:11:57 by moutig            #+#    #+#             */
/*   Updated: 2026/02/21 19:12:03 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hmath.h"

double	ft_pow(double base, double exp)
{
	if (exp == 0)
		return (1);
	if (base == 0)
		return (0);
	if (exp < 0)
		return (1 / ft_pow(base, -exp));

	double result = 1.0;
	double current_product = base;
	double current_exp = exp;

	while (current_exp > 1)
	{
		if ((int)current_exp % 2 == 1) /* if current_exp is odd */
			result *= current_product;

		current_product *= current_product; /* square the base */
		current_exp /= 2; /* integer division by 2 */
	}

	result *= current_product; /* account for the last factor */

	return (result);
}
