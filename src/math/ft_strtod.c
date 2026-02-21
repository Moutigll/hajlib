/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 19:10:23 by moutig            #+#    #+#             */
/*   Updated: 2026/02/21 20:27:06 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hstring.h"

#include "../../include/hmath.h"

double	ft_strtod(const char *str, char **endptr)
{
	double	result;
	int		sign;
	int		expSign;
	int		exp;

	while (*str == ' ' || (*str >= 9 && *str <= 13)) /* skip leading whitespace */
		str++;

	if (ft_strncmp(str, "nan", 3) == 0)
	{
		if (endptr)
			*endptr = (char *)(str + 3);
		return (0.0 / 0.0); /* Return NaN */
	}
	else if (ft_strncmp(str, "inf", 3) == 0)
	{
		if (endptr)
			*endptr = (char *)(str + 3);
		return (1.0 / 0.0); /* Return positive infinity */
	}
	else if (ft_strncmp(str, "-inf", 4) == 0)
	{
		if (endptr)
			*endptr = (char *)(str + 4);
		return (-1.0 / 0.0); /* Return negative infinity */
	}

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}

	result = 0.0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}

	if (*str == '.')
	{
		str++;
		double fracPart = 0.0;
		double divisor = 1.0;

		while (*str >= '0' && *str <= '9')
		{
			fracPart = fracPart * 10.0 + (*str - '0');
			divisor *= 10.0;
			str++;
		}
		result += fracPart / divisor;
	}

	expSign = 1;
	if (*str == 'e' || *str == 'E')
	{
		str++;
		if (*str == '+' || *str == '-')
		{
			if (*str == '-')
				expSign = -1;
			str++;
		}
		exp = 0;
		while (*str >= '0' && *str <= '9')
		{
			exp = exp * 10 + (*str - '0');
			str++;
		}
		result *= ft_pow(10.0, expSign * exp);
	}

	if (endptr != NULL)
		*endptr = (char *)str;

	return (sign * result);
}
