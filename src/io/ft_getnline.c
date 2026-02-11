/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:36:32 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:46:36 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/io.h"
#include "../../include/gnl.h"

int	ft_getnline(char *file)
{
	int		fd;
	char	*line;
	int		n;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = getNextLine(fd);
	n = 0;
	while (line)
	{
		n++;
		free(line);
		line = getNextLine(fd);
	}
	close(fd);
	return (n);
}
