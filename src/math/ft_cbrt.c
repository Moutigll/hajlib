/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cbrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 18:28:58 by moutig            #+#    #+#             */
/*   Updated: 2026/02/19 21:19:48 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hmath.h"

/* Compute cube root of a double using Newton-Raphson method */
double ft_cbrt(double x)
{
	if (x == 0.0)
		return (0.0);

	double guess = x;
	double prev = 0.0;

	while (ft_fabs(guess - prev) > 1e-10) // convergence threshold
	{
		prev = guess;
		guess = (2.0 * guess + x / (guess * guess)) / 3.0;
	}

	return (guess);
}
