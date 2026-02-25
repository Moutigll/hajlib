/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:09:46 by moutig            #+#    #+#             */
/*   Updated: 2026/02/25 14:10:26 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hmath.h"

double	ft_atod(const char *str)
{
	double	result;
	double	sign;
	double	fracPart;
	int		fracDivisor;

	result = 0.0;
	sign = 1.0;
	fracPart = 0.0;
	fracDivisor = 1;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1.0;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			fracPart = fracPart * 10.0 + (*str - '0');
			fracDivisor *= 10;
			str++;
		}
	}
	return (sign * (result + fracPart / fracDivisor));
}
