/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:17:42 by moutig            #+#    #+#             */
/*   Updated: 2026/02/16 16:38:46 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/hprintf.h"

int
printfEngine(t_printfBuffer	*buffer,
			const char		*format,
			va_list			ap)
{
	t_formatSpec	spec;
	va_list			apCopy;
	size_t			i;

	va_copy(apCopy, ap);

	i = 0;
	if (!format)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (parseFormat(format, &i, &spec) < 0)
				return (-1);
			if (dispatchFormat(buffer, &spec, &apCopy) < 0)
				return (-1);
		}
		else
		{
			if (bufferPutChar(buffer, format[i]) < 0)
				return (-1);
			i++;
		}
	}

	if (bufferFlush(buffer) < 0)
		return (-1);
	if (buffer->outputType == OUTPUT_BUFFER
		&& buffer->externalSize > 0)
	{
		if (buffer->externalIndex < buffer->externalSize)
			buffer->externalBuffer[buffer->externalIndex] = '\0';
		else
			buffer->externalBuffer[buffer->externalSize - 1] = '\0';
	}
	return ((int)buffer->totalWritten);
}
