/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:58:54 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:16 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hstring.h"
#include "../../include/hmath.h"

static int	ft_is_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int		base_len;
	int		result;
	int		value;

	base_len = ft_strlen(base);
	if (base_len < 2)
		return (0);
	result = 0;
	while (*str)
	{
		value = ft_is_in_base(*str, base);
		if (value == -1)
			break ;
		result = (result * base_len) + value;
		str++;
	}
	return (result);
}
