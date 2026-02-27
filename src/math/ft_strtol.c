/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:54:41 by moutig            #+#    #+#             */
/*   Updated: 2026/02/27 16:57:55 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "../../include/hchar.h"

#include "../../include/hmath.h"

static int	willOverflowLong(long acc, int digit, int base, int neg)
{
	long	cutoff;
	int		cutlim;

	if (neg)
	{
		/* For negative numbers, we're accumulating negative values */
		/* LONG_MIN = -LONG_MAX - 1, so careful */
		cutoff = LONG_MIN / base;
		cutlim = LONG_MIN % base;
		/* cutlim is negative, digit is positive, so we compare carefully */
		return (acc < cutoff || (acc == cutoff && -digit < cutlim));
	}
	else
	{
		cutoff = LONG_MAX / base;
		cutlim = LONG_MAX % base;
		return (acc > cutoff || (acc == cutoff && digit > cutlim));
	}
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	const char	*s = nptr;
	long		acc;
	int			c;
	int			neg;
	int			ovflw;
	int			digit;

	/* Skip white space */
	while (ft_isspace(*s))
		s++;

	/* Handle sign */
	neg = 0;
	if (*s == '-')
	{
		neg = 1;
		s++;
	}
	else if (*s == '+')
		s++;

	/* Handle base detection */
	if ((base == 0 || base == 16) && *s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
	{
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = (*s == '0') ? 8 : 10;

	acc = 0;
	ovflw = 0;
	while (1)
	{
		c = *s;

		/* Convert character to digit */
		digit = ft_charToDigit(c, base);
		if (digit < 0)
			break;

		s++;

		/* Check for overflow */
		if (ovflw < 0)
		{
			/* Already in overflow state, just continue */
			ovflw = -1;
		}
		else if (willOverflowLong(acc, digit, base, neg))
		{
			/* Overflow detected */
			ovflw = -1;
			/* Set to appropriate limit */
			if (neg)
				acc = LONG_MIN;
			else
				acc = LONG_MAX;
		}
		else
		{
			/* Normal conversion - accumulate positively then apply sign later */
			ovflw = 1;
			acc = acc * base + digit;
		}
	}

	/* If we never read any digits, no conversion */
	if (s == nptr || (s == nptr + 1 && (*(nptr) == '-' || *(nptr) == '+')))
	{
		if (endptr)
			*endptr = (char *)nptr;
		return (0);
	}

	/* Apply sign to positive accumulation */
	if (!ovflw || ovflw > 0)
	{
		if (neg)
			acc = -acc;
	}

	/* Set endptr to last character processed */
	if (endptr)
		*endptr = (char *)s;

	return (acc);
}
