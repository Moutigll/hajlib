/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_duplicates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:44:35 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/25 22:48:57 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_duplicate_at_index(char *str, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (str[i] == str[j])
			return (1);
		j++;
	}
	return (0);
}

void	ft_remove_duplicates(char *str)
{
	int	is_duplicate;
	int	len;
	int	i;
	int	k;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		is_duplicate = is_duplicate_at_index(str, i);
		if (is_duplicate)
		{
			k = i;
			while (k < len)
			{
				str[k] = str[k + 1];
				k++;
			}
			len--;
		}
		else
			i++;
	}
}
