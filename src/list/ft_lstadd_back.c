/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:29:08 by ele-lean          #+#    #+#             */
/*   Updated: 2024/10/16 18:39:40 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/list.h"

void	ft_lstadd_back(t_list **lst, t_list *newNode)
{
	t_list	*last;

	if (!lst || !newNode)
		return ;
	if (*lst == NULL)
	{
		*lst = newNode;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = newNode;
}
