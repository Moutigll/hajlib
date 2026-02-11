/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:20:53 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/07 17:26:46 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/math.h"

int	ft_atoi(const char *str)
{
	int		sign;
	int		result;

	sign = get_sign(&str);
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}
