/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:46:19 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/15 22:58:15 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hstring.h"
#include "../../include/hmath.h"

static char	*fracToStr(long long frac_val, int precision)
{
	char	*frac_part;
	int		i;

	frac_part = malloc(precision + 2); /* '.' + '\0' */
	if (!frac_part)
		return (NULL);

	frac_part[0] = '.';
	i = precision - 1;
	while (i >= 0)
	{
		frac_part[i + 1] = '0' + (frac_val % 10);
		frac_val /= 10;
		i--;
	}
	frac_part[precision + 1] = '\0';
	return (frac_part);
}

char	*ft_dtoa(double n, int precision)
{
	char			*frac_part;
	long long		frac_val;
	long long		int_val;
	long long		multiplier;
	int				i;

	if (precision < 0)
		precision = 6;

	int_val = (long long)n;
	if (n < 0)
		n = -n;

	multiplier = 1;
	i = 0;
	while (i < precision)
	{
		multiplier *= 10;
		i++;
	}

	frac_val = (long long)((n - (long long)n) * multiplier + 0.5);
	if (frac_val >= multiplier)
	{
		if (int_val >= 0)
			int_val += 1;
		else
			int_val -= 1;
		frac_val -= multiplier;
	}

	if (precision == 0)
		return (ft_itoa((int)int_val));

	frac_part = fracToStr(frac_val, precision);
	if (!frac_part)
		return (NULL);

	return (ft_strjoin_free(ft_itoa((int)int_val), frac_part, 1, 1));
}
