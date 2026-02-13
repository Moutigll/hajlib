/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 19:21:19 by moutig            #+#    #+#             */
/*   Updated: 2026/02/13 19:47:39 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/hprintf.h"

int
ft_printf(const char *format, ...)
{
	va_list			ap;
	t_printfBuffer	buffer;
	int				result;

	va_start(ap, format);
	bufferInitFd(&buffer, 1, FT_IO_LINE_BUFFERED);
	result = printfEngine(&buffer, format, ap);
	va_end(ap);
	return (result);
}

int
ft_dprintf(int fd, const char *format, ...)
{
	va_list			ap;
	t_printfBuffer	buffer;
	int				result;

	va_start(ap, format);
	bufferInitFd(&buffer, fd, FT_IO_FULL_BUFFERED);
	result = printfEngine(&buffer, format, ap);
	va_end(ap);
	return (result);
}

int
ft_vprintf(const char *format, va_list ap)
{
	t_printfBuffer	buffer;

	bufferInitFd(&buffer, 1, FT_IO_LINE_BUFFERED);
	return (printfEngine(&buffer, format, ap));
}

int
ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_printfBuffer	buffer;

	bufferInitFd(&buffer, fd, FT_IO_FULL_BUFFERED);
	return (printfEngine(&buffer, format, ap));
}

int
ft_snprintf(char *dst, size_t size, const char *format, ...)
{
	va_list			ap;
	t_printfBuffer	buffer;
	int				result;

	va_start(ap, format);
	bufferInitMemory(&buffer, dst, size);
	result = printfEngine(&buffer, format, ap);
	va_end(ap);
	return (result);
}

int
ft_vsnprintf(char *dst,
		size_t size,
		const char *format,
		va_list ap)
{
	t_printfBuffer	buffer;

	bufferInitMemory(&buffer, dst, size);
	return (printfEngine(&buffer, format, ap));
}
