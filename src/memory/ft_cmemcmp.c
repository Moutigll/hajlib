/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmemcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:24:08 by moutig            #+#    #+#             */
/*   Updated: 2026/06/13 15:26:29 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hmemory.h"

int	ft_cmemcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	volatile int		result;
	size_t				i;

	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	result = 0;
	i = 0;
	while (i < n)
	{
		result |= (ptr1[i] ^ ptr2[i]);
		i++;
	}
	return (result == 0);
}
