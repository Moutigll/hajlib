/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:42:29 by moutig            #+#    #+#             */
/*   Updated: 2026/02/15 23:01:31 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "../../../include/hmath.h"
#include "../../../include/hstring.h"

#include "../../../include/hprintf.h"

int
handleInt(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap)
{
	char	*s;
	int		val;
	int		ret;

	val = va_arg(ap, int);
	s = ft_itoa(val);
	if (!s)
		return (-1);

	if (s[0] == '-' && spec->zeroPad && !spec->leftAlign && !spec->centerAlign) /* Handle negative numbers with zero padding */
	{
		/* write sign */
		if (bufferPutChar(buffer, '-') < 0)
		{
			free(s);
			return (-1);
		}
		/* emit digits without sign, and width decreased by 1 for sign */
		ret = emitFormatted(buffer, spec, s + 1, ft_strlen(s + 1));
		free(s);
		return (ret);
	}
	/* default: print whole string (with sign) */
	ret = emitFormatted(buffer, spec, s, ft_strlen(s));
	free(s);
	return (ret);
}

int
handleUnsigned(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap)
{
	char			*s;
	unsigned int	val;
	int				ret;

	val = va_arg(ap, unsigned int);
	s = ft_utoa(val);
	if (!s)
		return (-1);
	ret = emitFormatted(buffer, spec, s, ft_strlen(s));
	free(s);
	return (ret);
}


int
handleHex(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap)
{
	char			*s;
	unsigned int	val;
	int				upper;
	int				ret;

	val = va_arg(ap, unsigned int);
	upper = (spec->specifier == 'X');
	s = ft_utoa_base(val, 16, upper);
	if (!s)
		return (-1);
	ret = emitFormatted(buffer, spec, s, ft_strlen(s));
	free(s);
	return (ret);
}

int
handlePointer(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap)
{
	char	*addr;
	char	*full;
	void	*ptr;
	int		ret;

	ptr = va_arg(ap, void *);
	addr = ft_utoa_base((unsigned long)ptr, 16, 0);
	if (!addr)
		return (-1);
	full = ft_strjoin("0x", addr);
	free(addr);
	if (!full)
		return (-1);
	ret = emitFormatted(buffer, spec, full, ft_strlen(full));
	free(full);
	return (ret);
}

int
handleFloat(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap)
{
	char	*s;
	double	val;
	int		ret;

	val = va_arg(ap, double);
	s = ft_dtoa(val, 
		spec->hasPrecision ? spec->precision : 6);
	if (!s)
		return (-1);

	if (s[0] == '-' && spec->zeroPad && !spec->leftAlign && !spec->centerAlign)
	{
		/* write sign */
		if (bufferPutChar(buffer, '-') < 0)
		{
			free(s);
			return (-1);
		}
		/* emit digits without sign, and width decreased by 1 for sign */
		ret = emitFormatted(buffer, spec, s + 1, ft_strlen(s + 1));
		free(s);
		return (ret);
	}
	/* default: print whole string (with sign) */
	ret = emitFormatted(buffer, spec, s, ft_strlen(s));
	free(s);
	return (ret);
	return (ret);
}
