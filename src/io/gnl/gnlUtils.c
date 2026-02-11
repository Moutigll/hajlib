/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:25:58 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/07 02:35:17 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/gnl.h"

void	gnlLstaddBack(t_list **list, char *buffer, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(list[fd]);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		list[fd] = new_node;
	else
		last_node->next = new_node;
	new_node->content = buffer;
	new_node->next = NULL;
}

void	freeGnlList(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (NULL == *list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (CONTENT(clean_node)[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}