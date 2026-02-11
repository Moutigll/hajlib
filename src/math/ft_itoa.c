/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:45:13 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:16 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hstring.h"
#include "../../include/hmath.h"

static int	gesize_t(int n, int sign)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (sign == -1)
		size = 1;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*conver_num(int n, char *res, int size, int sign)
{
	res[size] = '\0';
	while (size > 0)
	{
		res[size - 1] = (n % 10) + '0';
		n /= 10;
		size--;
	}
	if (sign == -1)
		res[0] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		size;
	int		sign;

	if (n == -2147483648)
	{
		res = (char *)malloc(sizeof(char) * 12);
		if (!res)
			return (0);
		ft_strlcpy(res, "-2147483648", 12);
		return (res);
	}
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		n *= -1;
	}
	size = gesize_t(n, sign);
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (0);
	return (conver_num(n, res, size, sign));
}
