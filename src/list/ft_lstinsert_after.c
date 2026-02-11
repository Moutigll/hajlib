/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_after.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:14:23 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/30 14:16:13 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstinsert_after(t_list *current, t_list *new_node)
{
	t_list	*next;

	if (!current || !new_node)
		return ;
	next = current->next;
	current->next = new_node;
	new_node->next = next;
}
