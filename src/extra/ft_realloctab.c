/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloctab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:31:51 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/07 11:37:45 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_realloctab(void **array, size_t old_size, size_t new_size)
{
	void	**new_array;
	size_t	i;

	new_array = (void **)malloc(new_size * sizeof(void *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < old_size && i < new_size)
	{
		new_array[i] = array[i];
		i++;
	}
	while (i < new_size)
	{
		new_array[i] = NULL;
		i++;
	}
	free(array);
	return (new_array);
}
