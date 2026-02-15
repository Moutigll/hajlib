/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:46:36 by moutig            #+#    #+#             */
/*   Updated: 2026/02/15 21:48:26 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hmath.h"

char	*ft_utoa_base(unsigned int n, unsigned int base, int upper)
{
	char		*digits;
	char		*str;
	size_t		len;

	if (base < 2 || base > 16)
		return (NULL);
	digits = upper ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				   : "0123456789abcdefghijklmnopqrstuvwxyz";
	len = ft_numlen(n, base);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[--len] = digits[n % base];
		n /= base;
	}
	return (str);
}
