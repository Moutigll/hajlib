/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 19:15:38 by moutig            #+#    #+#             */
/*   Updated: 2026/02/27 16:57:37 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "../../include/hchar.h"

#include "../../include/hmath.h"

static int	willOverflow(unsigned long acc, int digit, int base)
{
	unsigned long	cutoff;
	int				cutlim;

	cutoff = ULONG_MAX / (unsigned long)base;
	cutlim = ULONG_MAX % (unsigned long)base;
	
	return (acc > cutoff || (acc == cutoff && digit > cutlim));
}


unsigned long	ft_strtoul(const char *nptr, char **endptr, int base)
{
	const char		*s = nptr;
	unsigned long	acc;
	int				c;
	int				neg;
	int				ovflw;

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
		c = *s++;

		/* Convert character to digit */
		c = ft_charToDigit(c, base);
		if (c < 0)
			break;

		/* Check for overflow */
		if (ovflw < 0)
			/* Already in overflow state, just continue */
			ovflw = -1;
		else if (willOverflow(acc, 	c, base))
		{
			/* Overflow detected */
			ovflw = -1;
			acc = ULONG_MAX;
		}
		else
		{
			/* Normal conversion */
			ovflw = 1;
			acc = acc * base + c;
		}
	}

	/* Handle negative values */
	if (neg && ovflw > 0)
		acc = -acc;

	/* Set endptr */
	if (endptr)
	{
		if (ovflw)
			*endptr = (char *)(s - 1);
		else
			*endptr = (char *)nptr;
	}

	return (acc);
}
