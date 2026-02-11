/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:10:38 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:01 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hmemory.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*mem;

	i = 0;
	mem = (const unsigned char *)s;
	while (i < n)
	{
		if (mem[i] == (unsigned char)c)
			return ((void *)&mem[i]);
		i++;
	}
	return (0);
}
