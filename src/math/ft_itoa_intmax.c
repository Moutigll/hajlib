/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_intmax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:36:08 by moutig            #+#    #+#             */
/*   Updated: 2026/05/19 15:37:16 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hmath.h"

char *ft_itoa_intmax(intmax_t n)
{
	char		*str;
	intmax_t	tmp = n;
	size_t		len = (n <= 0) ? 1 : 0;

	while (tmp) {
		tmp /= 10;
		len++;
	}
	str = malloc(len + 1);
	if (!str) return (NULL);
	str[len] = '\0';
	if (n < 0) str[0] = '-';
	if (n == 0) str[0] = '0';
	while (n) {
		str[--len] = (n % 10) * ((n > 0) ? 1 : -1) + '0';
		n /= 10;
	}
	return (str);
}
