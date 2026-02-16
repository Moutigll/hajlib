/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:37:44 by moutig            #+#    #+#             */
/*   Updated: 2026/02/16 14:41:10 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hmath.h"

#define PI	3.14159265358979323846264338327950288
#define TAU	6.28318530717958647692528676655900576

double ft_sin(double x)
{
	/* 1) reduce x to range [-pi, pi] */
	double n = (double)((int)(x / TAU));
	x = x - n * TAU;

	if (x > PI)
		x -= TAU;

	int sign = 1;
	if (x > (PI / 2.0))
		x = PI - x;
	else if (x < -(PI / 2.0))
	{
		x = -PI - x;
		sign = -1;
	}

	/* 2) compute Taylor series around 0 for reduced x (|x| <= pi/2) */
	double term = x;	   /* first term = x */
	double sum  = term;
	double x2   = x * x;
	int curSign = -1;

	/* use more terms for stability (15 terms total) */
	for (int k = 1; k <= 14; k++)
	{
		/* term_k = term_{k-1} * x^2 / ((2k)*(2k+1)) */
		term *= x2 / ((2.0 * k) * (2.0 * k + 1.0));
		sum += curSign * term;
		curSign = -curSign;
	}

	return (sign * sum);
}
