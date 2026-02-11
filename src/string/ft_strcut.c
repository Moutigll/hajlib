/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:34:46 by tle-goff          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:16 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hstring.h"

char	*ft_strcut(char *str, char c)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != c)
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
