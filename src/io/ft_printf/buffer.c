/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:00:07 by moutig            #+#    #+#             */
/*   Updated: 2026/02/13 19:35:49 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/hprintf.h"


void
bufferInitFd(t_printfBuffer *buffer, int fd, int mode)
{
	buffer->index = 0;
	buffer->totalWritten = 0;
	buffer->fd = fd;
	buffer->externalBuffer = NULL;
	buffer->externalSize = 0;
	buffer->externalIndex = 0;
	buffer->bufferMode = mode;
	buffer->outputType = OUTPUT_FD;
}

void
bufferInitMemory(t_printfBuffer *buffer, char *dst, size_t size)
{
	buffer->index = 0;
	buffer->totalWritten = 0;
	buffer->fd = -1;
	buffer->externalBuffer = dst;
	buffer->externalSize = size;
	buffer->externalIndex = 0;
	buffer->bufferMode = FT_IO_FULL_BUFFERED;
	buffer->outputType = OUTPUT_BUFFER;
}

int
bufferFlush(t_printfBuffer *buffer)
{
	ssize_t	written;

	if (buffer->index == 0)
		return (0);
	if (buffer->outputType == OUTPUT_FD)
	{
		written = write(buffer->fd,
				buffer->internalBuffer,
				buffer->index);
		if (written < 0)
			return (-1);
	}
	buffer->index = 0;
	return (0);
}


int
bufferPutChar(t_printfBuffer *buffer, char c)
{
	if (buffer->outputType == OUTPUT_BUFFER)
	{
		if (buffer->externalIndex + 1 < buffer->externalSize)
			buffer->externalBuffer[buffer->externalIndex] = c;
		buffer->externalIndex++;
		buffer->totalWritten++;
		return (0);
	}
	buffer->internalBuffer[buffer->index] = c;
	buffer->index++;
	buffer->totalWritten++;
	if (buffer->bufferMode == FT_IO_UNBUFFERED)
		return (bufferFlush(buffer));
	if (buffer->bufferMode == FT_IO_LINE_BUFFERED && c == '\n')
		return (bufferFlush(buffer));
	if (buffer->index >= FT_PRINTF_BUFFER_SIZE)
		return (bufferFlush(buffer));
	return (0);
}

	
int
bufferWrite(t_printfBuffer	*buffer,
			const char		*data,
			size_t			len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (bufferPutChar(buffer, data[i]) < 0)
			return (-1);
		i++;
	}
	return (0);
}
