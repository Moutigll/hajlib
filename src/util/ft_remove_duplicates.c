/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_duplicates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 22:44:35 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:52 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hstring.h"
#include "../../include/hutils.h"

static int	is_duplicate_at_index(char *str, int i)
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
