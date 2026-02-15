/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:25:45 by moutig            #+#    #+#             */
/*   Updated: 2026/02/15 23:41:24 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "../../../include/hstring.h"

#include "../../../include/hprintf.h"

static int
applyPadding(t_formatSpec *spec, size_t pad, int isLeft, t_printfBuffer *buffer)
{
	size_t	padding;
	size_t	i;
	char	padChar;

	padChar = ' ';
	if (spec->zeroPad && !spec->leftAlign
		&& !spec->centerAlign && spec->specifier != 's')
		padChar = '0';

	if (isLeft)
	{
		if (spec->centerAlign)
			padding = pad / 2;
		else if (spec->leftAlign)
			padding = 0;
		else
			padding = pad;
	}
	else
	{
		if (spec->centerAlign)
			padding = pad - (pad / 2);
		else if (spec->leftAlign)
			padding = pad;
		else
			padding = 0;
	}

	/* LEFT PAD */
	i = 0;
	while (i < padding)
	{
		if (bufferPutChar(buffer, padChar) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int
emitFormatted(t_printfBuffer *buffer,
			t_formatSpec *spec,
			const char *s,
			size_t len)
{
	size_t	blockLen;
	size_t	finalLen;
	size_t	pad;
	size_t	i;
	size_t	written;
	int		truncated;

	truncated = 0;
	blockLen = len;

	if (spec->repeat <= 0)
		spec->repeat = 1;

	finalLen = blockLen * (size_t)spec->repeat;

	if (spec->truncate && spec->width > 0
		&& (size_t)spec->width < finalLen)
	{
		finalLen = (size_t)spec->width - 1; /* reserve space for '.' */
		truncated = 1;
	}

	/* compute padding (only if NOT truncated) */
	if (!truncated && spec->width > (int)finalLen)
		pad = (size_t)spec->width - finalLen;
	else
		pad = 0;

	/* LEFT PAD */
	if (applyPadding(spec, pad, 1, buffer) < 0)
		return (-1);

	/* CONTENT */
	written = 0;
	while ((size_t)spec->repeat && written < finalLen)
	{
		i = 0;
		while (i < blockLen && written < finalLen)
		{
			if (bufferPutChar(buffer, s[i]) < 0)
				return (-1);
			written++;
			i++;
		}
		spec->repeat--;
	}

	/* replace last char with '.' if truncated */
	if (truncated && finalLen > 0)
	{
		if (bufferPutChar(buffer, '.') < 0)
			return (-1);
	}

	/* RIGHT PAD */
	if (applyPadding(spec, pad, 0, buffer) < 0)
		return (-1);

	return (0);
}

int
dispatchFormat(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap)
{
	if (spec->specifier == '%')
		return (emitFormatted(buffer, spec, "%", 1));
	if (spec->specifier == 'c')
	{
		char	c;
		c = (char)va_arg(ap, int);
		/* %c: precision ignored, repeat supported */
		return (emitFormatted(buffer, spec, &c, 1));
	}
	if (spec->specifier == 's')
	{
		char	*s;
		size_t	len;
		s = va_arg(ap, char *);
		if (!s)
			s = "(null)";
		len = ft_strlen(s);
		if (spec->hasPrecision && spec->precision < (int)len)
			len = spec->precision;
		return (emitFormatted(buffer, spec, s, len));
	}
	if (spec->specifier == 'd' || spec->specifier == 'i')
		return (handleInt(buffer, spec, ap));
	if (spec->specifier == 'u')
		return (handleUnsigned(buffer, spec, ap));
	if (spec->specifier == 'x' || spec->specifier == 'X')
		return (handleHex(buffer, spec, ap));
	if (spec->specifier == 'p')
		return (handlePointer(buffer, spec, ap));
	if (spec->specifier == 'f')
		return (handleFloat(buffer, spec, ap));
	return (-1);
}
