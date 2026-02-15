/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:38:42 by moutig            #+#    #+#             */
/*   Updated: 2026/02/15 21:40:13 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hmath.h"

size_t	ft_numlen(unsigned int n, unsigned int base)
{
	size_t	len;

	if (base < 2)
		return (0);
	len = 1;
	while (n >= base)
	{
		n /= base;
		len++;
	}
	return (len);
}
