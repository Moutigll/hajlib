/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_removenode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:50:22 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/07 11:58:25 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	rm_node(t_list *current,
	t_list *prev, t_list **head, void (*del)(void *))
{
	t_list	*temp;

	temp = current;
	if (prev)
		prev->next = current->next;
	else
		*head = current->next;
	current = current->next;
	if (del)
		del(temp->content);
	free(temp);
}

void	ft_removenode(t_list **head, void *to_remove, void (*del)(void *))
{
	t_list	*current;
	t_list	*prev;

	if (!head || !*head)
		return ;
	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->content == to_remove)
			rm_node(current, prev, head, del);
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
