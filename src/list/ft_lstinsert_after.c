/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_after.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:14:23 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:09:10 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hlist.h"

void	ft_lstinsert_after(t_list *current, t_list *new_node)
{
	t_list	*next;

	if (!current || !new_node)
		return ;
	next = current->next;
	current->next = new_node;
	new_node->next = next;
}
