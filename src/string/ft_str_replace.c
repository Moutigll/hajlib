/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:33:34 by ele-lean          #+#    #+#             */
/*   Updated: 2025/01/22 22:40:17 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_occurrences(char *str, char *to_replace)
{
	size_t	count;
	char	*current;
	int		to_replace_len;

	count = 0;
	to_replace_len = ft_strlen(to_replace);
	if (str && to_replace && *to_replace)
	{
		current = str;
		while (current)
		{
			current = ft_strstr(current, to_replace);
			if (current)
			{
				count++;
				current += to_replace_len;
			}
		}
	}
	return (count);
}

static size_t	calculate_new_str_len(char *str,
	char *to_replace, char *replacement)
{
	size_t	to_replace_len;
	size_t	replacement_len;
	size_t	new_str_len;

	to_replace_len = ft_strlen(to_replace);
	replacement_len = ft_strlen(replacement);
	new_str_len = ft_strlen(str) + count_occurrences(str, to_replace)
		* (replacement_len - to_replace_len) + 1;
	return (new_str_len);
}

static char	*replace_occurrences(char *str,
	char *to_replace, char *replacement, char *new_str_pos)
{
	char	*current;
	char	*match;
	size_t	to_replace_len;

	to_replace_len = ft_strlen(to_replace);
	current = str;
	while (*current)
	{
		match = ft_strstr(current, to_replace);
		if (match == current)
		{
			ft_memcpy(new_str_pos, replacement, ft_strlen(replacement));
			new_str_pos += ft_strlen(replacement);
			current += to_replace_len;
		}
		else
		{
			*new_str_pos++ = *current++;
		}
	}
	*new_str_pos = '\0';
	return (new_str_pos);
}

char	*ft_str_replace(char *str, char *to_replace, char *replacement)
{
	char	*new_str_pos;
	size_t	new_str_len;

	if (!str || !to_replace || !replacement)
		return (NULL);
	new_str_len = calculate_new_str_len(str, to_replace, replacement);
	new_str_pos = malloc(new_str_len);
	if (!new_str_pos)
		return (NULL);
	replace_occurrences(str, to_replace, replacement, new_str_pos);
	return (new_str_pos);
}
