/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:03:18 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:10:52 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hmemory.h"
#include "../../include/hstring.h"
#include "../../include/hutils.h"

char	*ft_addchar(char *str, char c)
{
	size_t	len;
	char	*new;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	ft_memcpy(new, str, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}
