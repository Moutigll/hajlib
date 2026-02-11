/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:02:29 by ele-lean          #+#    #+#             */
/*   Updated: 2024/10/16 16:30:54 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/string.h"

static int	countWords(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	clen;

	if (!s)
		return (0);
	tab = (char **)malloc(sizeof(char *) * (countWords(s, c) + 1));
	if (!tab)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			clen = 0;
			while (s[clen] != c && s[clen])
				clen++;
			tab[i++] = ft_substr(s, 0, clen);
			while (*s != c && *s)
				s++;
		}
	}
	tab[i] = 0;
	
	return (tab);
}
