/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:36:56 by moutig            #+#    #+#             */
/*   Updated: 2026/02/15 21:40:32 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hmath.h"

char	*ft_utoa(unsigned int n)
{
	char	*str;
	size_t	len;

	len = ft_numlen(n, 10);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		str[--len] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}
