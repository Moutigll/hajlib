/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:36:32 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:08:46 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../include/hio.h"
#include "../../include/hgnl.h"

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
