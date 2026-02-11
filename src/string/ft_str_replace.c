/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 21:33:34 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:16 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hstring.h"


char	*ft_str_replace(char *str, char *to_replace, char *replacement)
{
	char	**parts;
	char	*result;
	char	*tmp;
	int		i;

	if (!str || !to_replace || !replacement)
		return (NULL);

	parts = ft_split(str, to_replace[0]);
	if (!parts)
		return (NULL);

	result = ft_strdup(parts[0]);
	if (!result)
	{
		free(parts);
		return (NULL);
	}

	i = 1;
	while (parts[i])
	{
		tmp = ft_strjoin(result, replacement);
		free(result);
		result = ft_strjoin(tmp, parts[i]);
		free(tmp);
		i++;
	}

	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);

	return (result);
}
