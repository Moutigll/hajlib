/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_font.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:29:48 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/21 07:07:33 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	create_letter(t_mlx_font *font, int index)
{
	t_mlx_letter	*letter;

	if (!font->letters_str)
	{
		printf("Error: Font letters string is not initialized\n");
		return (0);
	}

	letter = malloc(sizeof(t_mlx_letter));
	if (!letter)
	{
		printf("Error: Failed to allocate memory for letter\n");
		return (0);
	}

	ft_bzero(letter, sizeof(t_mlx_letter));

	font->letters[index] = *letter;
	free(letter);
	return (1);
}

static int	assign_dim(char *line, t_mlx_letter *letter)
{
	char	**split;

	split = ft_split(line, ',');
	if (!split || ft_tablen((void **)split) < 4
		|| ft_tablen((void **)split) > 5)
	{
		free_tab((void **)split);
		printf("Error: Invalid letter format\n");
		return (0);
	}
	letter->start_x = ft_atoi(split[0]);
	letter->start_y = ft_atoi(split[1]);
	letter->end_x = ft_atoi(split[2]);
	letter->end_y = ft_atoi(split[3]);
	if (split[4])
		letter->align = ft_atoi(split[4]);
	else
		letter->align = 0;
	free_tab((void **)split);
	return (1);
}

static int	get_font_line(int *i, int fd, t_mlx_font *font)
{
	char	*let_line;

	let_line = get_next_line(fd);
	while (let_line && ft_isdigit(let_line[0]))
	{
		if (!create_letter(font, *i)
			|| !assign_dim(let_line, font->letters + *i))
		{
			free(let_line);
			return (0);
		}
		(*i)++;
		free(let_line);
		let_line = get_next_line(fd);
	}
	free(let_line);
	return (1);
}

int	mlx_new_font(t_mlx_font *font)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(font->path, O_RDONLY);
	if (fd == -1)
		return (printf("Error: Failed to open font file\n"), 0);
	line = get_next_line(fd);
	while (line[0] == '\0' || line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	font->letters_str = ft_strdup(line);
	font->letters = malloc(sizeof(t_mlx_letter) * 100);
	font->font_size = FONT_SIZE;
	font->letter_spacing = FONT_SPACING;
	font->space_width = FONT_SPACE;
	i = 0;
	if (!get_font_line(&i, fd, font))
		return (close(fd), clear_mlx_font(font), 0);
	free(line);
	close(fd);
	return (1);
}
