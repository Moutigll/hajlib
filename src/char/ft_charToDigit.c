/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charToDigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:55:55 by moutig            #+#    #+#             */
/*   Updated: 2026/02/27 16:56:09 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/hchar.h"

int	ft_charToDigit(int c, int base)
{
	int	digit;

	if (ft_isdigit(c))
		digit = c - '0';
	else if (ft_isalpha(c))
	{
		if (c >= 'A' && c <= 'Z')
			digit = c - 'A' + 10;
		else
			digit = c - 'a' + 10;
	}
	else
		return (-1);
	
	if (digit >= base)
		return (-1);
	return (digit);
}
