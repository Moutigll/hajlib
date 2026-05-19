/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base_uintmax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:51:08 by moutig            #+#    #+#             */
/*   Updated: 2026/05/19 15:53:41 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hstring.h"
#include "../../include/hmath.h"

static size_t	ft_uintmax_len(uintmax_t n, size_t base_len)
{
	size_t	len;

	len = 1;
	while (n >= base_len)
	{
		n /= base_len;
		++len;
	}
	return (len);
}

char	*ft_utoa_base_uintmax(uintmax_t n, char *base)
{
	size_t	base_len;
	size_t	len;
	char	*str;

	if (!base)
		return (NULL);
	base_len = ft_strlen(base);
	if (base_len < 2)
		return (NULL);
	len = ft_uintmax_len(n, base_len);
	str = calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
		str[0] = base[0];
	while (n > 0)
	{
		str[--len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}
