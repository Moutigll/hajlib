/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:55:57 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:01 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hmemory.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	dest = (void *)malloc(nmemb * size);
	if (dest == 0)
		return (0);
	ft_bzero(dest, nmemb * size);
	return (dest);
}
