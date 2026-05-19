/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_uintmax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:38:03 by moutig            #+#    #+#             */
/*   Updated: 2026/05/19 15:38:43 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hmath.h"

char *ft_utoa_uintmax(uintmax_t n)
{
	char		*str;
	uintmax_t	tmp = n;
	size_t		len = (n == 0) ? 1 : 0;

	while (tmp) {
		tmp /= 10;
		len++;
	}
	str = malloc(len + 1);
	if (!str) return (NULL);
	str[len] = '\0';
	if (n == 0) str[0] = '0';
	while (n) {
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
