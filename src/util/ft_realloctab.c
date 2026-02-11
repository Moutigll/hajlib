/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloctab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:31:51 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:52 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../../include/hutils.h"

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
