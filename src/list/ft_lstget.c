/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:27:28 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/07 11:55:43 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/list.h"

t_list	*ft_lstget(t_list *list, int index)
{
	int	i;

	if (!list || index < 0)
		return (NULL);
	i = 0;
	while (list)
	{
		if (i == index)
			return (list);
		list = list->next;
		i++;
	}
	return (NULL);
}
