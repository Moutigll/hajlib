/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:25:41 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/30 13:33:30 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../../../include/gnl.h"

static int	findNl(t_list *list, t_newline *line)
{
	int	i;

	if (!list)
		return (0);
	line->size = 0;
	line->buffers = 0;
	while (list)
	{
		i = 0;
		line->buffers++;
		while (CONTENT(list)[i] && i < BUFFER_SIZE)
		{
			if (CONTENT(list)[i] == '\n')
				return (1);
			i++;
			line->size++;
		}
		list = list->next;
	}
	return (0);
}

static void	createList(t_list **list, int fd, t_newline *line)
{
	char	*buffer;
	int		size;

	while (!findNl(list[fd], line))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		size = read(fd, buffer, BUFFER_SIZE);
		if (!size || size == -1)
			return (free(buffer));
		buffer[size] = '\0';
		gnlLstaddBack(list, buffer, fd);
	}
}

static char	*extractLine(t_list *list, t_newline *line)
{
	char	*char_line;
	int		i;
	int		k;

	char_line = malloc(sizeof(char) * (line->size + 2));
	if (!char_line || !list)
		return (NULL);
	k = 0;
	while (list)
	{
		i = 0;
		while (CONTENT(list)[i])
		{
			if (CONTENT(list)[i] == '\n')
			{
				char_line[k++] = '\n';
				char_line[k] = '\0';
				return (char_line);
			}
			char_line[k++] = CONTENT(list)[i++];
		}
		list = list->next;
	}
	char_line[k] = '\0';
	return (char_line);
}

static void	cleanList(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
		return ;
	last_node = ft_lstlast(*list);
	i = 0;
	k = 0;
	while (CONTENT(last_node)[i] && CONTENT(last_node)[i] != '\n')
		i++;
	while (CONTENT(last_node)[i] && CONTENT(last_node)[++i])
		buf[k++] = CONTENT(last_node)[i];
	buf[k] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	freeGnlList(list, clean_node, buf);
}

char	*getNextLine(int fd)
{
	static t_list	*list[4096];
	char			*next_line;
	t_newline		*line;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(t_newline));
	if (!line)
		return (NULL);
	createList(list, fd, line);
	if (!list[fd])
	{
		free(line);
		return (NULL);
	}
	next_line = extractLine(list[fd], line);
	cleanList(&list[fd]);
	free(line);
	return (next_line);
}
