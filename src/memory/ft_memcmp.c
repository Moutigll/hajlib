/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:26:30 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:01 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hmemory.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*mem1;
	const unsigned char	*mem2;

	i = 0;
	mem1 = (const unsigned char *)s1;
	mem2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (mem1[i] != mem2[i])
			return (mem1[i] - mem2[i]);
		i++;
	}
	return (0);
}
