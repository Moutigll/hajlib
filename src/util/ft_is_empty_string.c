/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_empty_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:56:21 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:52 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hutils.h"

int	ft_is_empty_string(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (str[0] != ' ' && str[0] != '\t' && str[0] != '\n'
			&& str[0] != '\v' && str[0] != '\f' && str[0] != '\r')
			return (0);
		str++;
	}
	return (1);
}
