/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:46:19 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/21 08:53:35 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dtoa(double n, int precision)
{
	char	*str;
	char	*int_part;
	char	*frac_part;
	int		i;
	int		frac_n;

	if (precision < 0)
		precision = 2;
	frac_n = (int)((n - (int)n) * 10 * precision);
	if (frac_n < 0)
		frac_n *= -1;
	int_part = ft_itoa((int)n);
	frac_part = malloc(precision + 2);
	if (!frac_part)
		return (NULL);
	frac_part[0] = '.';
	i = 1;
	while (precision--)
	{
		frac_part[i++] = (frac_n % 10) + '0';
		frac_n /= 10;
	}
	frac_part[i] = '\0';
	str = ft_strjoin_free(int_part, frac_part, 1, 1);
	return (str);
}
