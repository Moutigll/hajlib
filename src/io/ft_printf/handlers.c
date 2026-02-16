/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:42:29 by moutig            #+#    #+#             */
/*   Updated: 2026/02/16 10:48:59 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "../../../include/hmath.h"
#include "../../../include/hmemory.h"
#include "../../../include/hstring.h"

#include "../../../include/hprintf.h"

static char *
applyNumberPrecision(t_formatSpec *spec, char *digits)
{
	size_t	len;
	size_t	zeros;
	char	*newstr;
	size_t	i;

	if (!spec->hasPrecision)
		return (digits);

	spec->zeroPad = 0;

	len = ft_strlen(digits);

	/* 0 value with precision 0 => empty string */
	if (spec->precision == 0 && len == 1 && digits[0] == '0')
	{
		digits[0] = '\0';
		return (digits);
	}

	if ((size_t)spec->precision <= len)
		return (digits);

	zeros = spec->precision - len;

	newstr = malloc(spec->precision + 1);
	if (!newstr)
	{
		free(digits);
		return (NULL);
	}

	i = 0;
	while (i < zeros)
		newstr[i++] = '0';

	ft_memcpy(newstr + zeros, digits, len + 1);
	free(digits);
	return (newstr);
}

int
handleInt(t_printfBuffer *buffer, t_formatSpec *spec, va_list *ap)
{
	char	*s;
	char	*digits;
	int		val;
	int		ret;
	int		isNeg;

	val = va_arg(*ap, int);
	isNeg = (val < 0);

	s = ft_itoa(val);
	if (!s)
		return (-1);

	if (isNeg)
		digits = ft_strdup(s + 1);
	else
		digits = ft_strdup(s);

	free(s);
	if (!digits)
		return (-1);

	digits = applyNumberPrecision(spec, digits);
	if (!digits)
		return (-1);

	if (isNeg)
	{
		char *tmp = ft_strjoin("-", digits);
		spec->width--; /* account for sign in width */
		free(digits);
		digits = tmp;
		if (!digits)
			return (-1);
	}

	ret = emitFormatted(buffer, spec, digits, ft_strlen(digits));
	free(digits);
	return (ret);
}

int
handleUnsigned(t_printfBuffer *buffer, t_formatSpec *spec, va_list *ap)
{
	char			*s;
	unsigned int	val;
	int				ret;

	val = va_arg(*ap, unsigned int);
	s = ft_utoa(val);
	if (!s)
		return (-1);

	s = applyNumberPrecision(spec, s);
	if (!s)
		return (-1);

	ret = emitFormatted(buffer, spec, s, ft_strlen(s));
	free(s);
	return (ret);
}

int
handleHex(t_printfBuffer *buffer, t_formatSpec *spec, va_list *ap)
{
	char			*s;
	unsigned int	val;
	int				upper;
	int				ret;

	val = va_arg(*ap, unsigned int);
	upper = (spec->specifier == 'X');
	s = ft_utoa_base(val, 16, upper);
	if (!s)
		return (-1);

	s = applyNumberPrecision(spec, s);
	if (!s)
		return (-1);

	ret = emitFormatted(buffer, spec, s, ft_strlen(s));
	free(s);
	return (ret);
}

int
handlePointer(t_printfBuffer *buffer, t_formatSpec *spec, va_list *ap)
{
	char	*addr;
	char	*full;
	void	*ptr;
	int		ret;

	ptr = va_arg(*ap, void *);

	if (!ptr)
		return (emitFormatted(buffer, spec, "(nil)", 5));

	addr = ft_utoa_base((uintptr_t)ptr, 16, 0);
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
handleFloat(t_printfBuffer *buffer, t_formatSpec *spec, va_list *ap)
{
	char	*s;
	double	val;
	int		ret;

	val = va_arg(*ap, double);
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
		spec->width--; /* account for sign in width */
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
