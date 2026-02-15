/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:46:36 by moutig            #+#    #+#             */
/*   Updated: 2026/02/15 23:50:47 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hmath.h"

static size_t	ft_numlen_u64(uintptr_t n, int base)
{
	size_t	len;

	len = 1;
	while (n >= (uintptr_t)base)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_utoa_base(uintptr_t value, int base, int upper)
{
	char			*digits;
	char			*str;
	size_t			len;

	if (base < 2 || base > 16)
		return (NULL);

	digits = upper ?
		"0123456789ABCDEF" :
		"0123456789abcdef";

	len = ft_numlen_u64(value, base);
	str = malloc(len + 1);
	if (!str)
		return (NULL);

	str[len] = '\0';

	while (len--)
	{
		str[len] = digits[value % base];
		value /= base;
	}

	return (str);
}
