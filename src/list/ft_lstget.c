/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:27:28 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:09:10 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hlist.h"

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
