/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:58:54 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/20 16:59:04 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_in_base(char c, char *base)
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
