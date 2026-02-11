/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:29:08 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:09:10 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hlist.h"

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
