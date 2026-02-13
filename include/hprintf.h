/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hprintf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:53:40 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/13 19:36:44 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HAJLIB_PRINTF_H
# define HAJLIB_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

/* ============================ CONFIGURATION ============================ */

# define FT_IO_UNBUFFERED		0
# define FT_IO_LINE_BUFFERED	1
# define FT_IO_FULL_BUFFERED	2

# define FT_PRINTF_BUFFER_SIZE	1024

/* ============================ FORMAT STRUCTURE ============================ */

/**
 * @brief Represents a parsed format specification.
 *
 * Contains all extracted components from a format sequence:
 * flags, width, precision, length modifier, specifier,
 * and custom extension parameters.
 */
typedef struct s_formatSpec
{
	char	flags[6];
	int		width;
	int		precision;
	char	length[3];
	char	spec;

	char	padChar;
	char	align;
	int		truncate;
}	t_formatSpec;

/* ============================ OUTPUT TARGET ============================ */

/**
 * @brief Defines the output type for printf.
 *
 * OUTPUT_FD      -> write to file descriptor
 * OUTPUT_BUFFER  -> write to memory buffer (snprintf mode)
 */
typedef enum e_outputType
{
	OUTPUT_FD,
	OUTPUT_BUFFER
}	t_outputType;

/**
 * @brief Represents the internal state of the printf buffer.
 *
 * Handles:
 * - internal temporary buffer
 * - file descriptor writing
 * - memory buffer writing (snprintf)
 * - flush management
 * - tracking total written characters
 */
typedef struct s_printfBuffer
{
	char			internalBuffer[FT_PRINTF_BUFFER_SIZE];
	size_t			index;
	size_t			totalWritten;

	int				fd;

	char			*externalBuffer;
	size_t			externalSize;
	size_t			externalIndex;

	int				bufferMode;
	t_outputType	outputType;
}	t_printfBuffer;

/* ============================ PUBLIC API ============================ */

/**
 * @brief Prints formatted output to stdout.
 */
int		ft_printf(const char *format, ...);

/**
 * @brief Prints formatted output to a file descriptor.
 */
int		ft_dprintf(int fd, const char *format, ...);

/**
 * @brief vprintf equivalent using va_list.
 */
int		ft_vprintf(const char *format, va_list ap);

/**
 * @brief vdprintf equivalent using va_list.
 */
int		ft_vdprintf(int fd, const char *format, va_list ap);

/**
 * @brief Writes formatted output to a memory buffer.
 *
 * Behaves similarly to snprintf.
 */
int		ft_snprintf(char *dst,
			size_t size,
			const char *format,
			...);

/**
 * @brief vsnprintf equivalent using va_list.
 */
int		ft_vsnprintf(char *dst,
			size_t size,
			const char *format,
			va_list ap);

/* ============================ CORE ENGINE ============================ */

/**
 * @brief Core formatting engine.
 *
 * Parses the format string and dispatches each
 * format specification to the appropriate handler.
 */
int		printfEngine(t_printfBuffer *buffer,
			const char *format,
			va_list ap);

/* ============================ BUFFER MANAGEMENT ============================ */

/**
 * @brief Initializes a buffer for file descriptor output.
 */
void	bufferInitFd(t_printfBuffer *buffer,
			int fd,
			int mode);

/**
 * @brief Initializes a buffer for memory output.
 */
void	bufferInitMemory(t_printfBuffer *buffer,
			char *dst,
			size_t size);

/**
 * @brief Flushes the internal buffer to its output target.
 */
int		bufferFlush(t_printfBuffer *buffer);

/**
 * @brief Writes raw data into the buffer.
 */
int		bufferWrite(t_printfBuffer *buffer,
			const char *data,
			size_t len);

/**
 * @brief Writes a single character into the buffer.
 */
int		bufferPutChar(t_printfBuffer *buffer,
			char c);

/* ============================ PARSING ============================ */

/**
 * @brief Initializes a format specification structure.
 */
void	ft_initFormatSpec(t_formatSpec *format);

/**
 * @brief Parses a format sequence starting after '%'.
 *
 * Fills the formatSpec structure accordingly.
 */
const char	*ft_parseFormat(const char *str,
					t_formatSpec *format,
					va_list *ap);

/**
 * @brief Handles a fully parsed format specification.
 */
int		ft_handleFormat(t_printfBuffer *buffer,
			t_formatSpec *format,
			va_list *ap);

/* ============================ SPECIFIER HANDLERS ============================ */

/**
 * @brief Handles %c specifier.
 */
int		ft_printChar(t_printfBuffer *buffer,
			t_formatSpec *format,
			va_list *ap);

/**
 * @brief Handles %s specifier.
 */
int		ft_printString(t_printfBuffer *buffer,
			t_formatSpec *format,
			va_list *ap);

/**
 * @brief Handles signed integer specifiers.
 */
int		ft_printInteger(t_printfBuffer *buffer,
			t_formatSpec *format,
			va_list *ap);

/**
 * @brief Handles unsigned integer specifiers.
 */
int		ft_printUnsigned(t_printfBuffer *buffer,
			t_formatSpec *format,
			va_list *ap);

/**
 * @brief Handles hexadecimal specifiers.
 */
int		ft_printHex(t_printfBuffer *buffer,
			t_formatSpec *format,
			va_list *ap);

/**
 * @brief Handles pointer specifier.
 */
int		ft_printPointer(t_printfBuffer *buffer,
			t_formatSpec *format,
			va_list *ap);

/**
 * @brief Handles floating point specifiers.
 */
int		ft_printFloat(t_printfBuffer *buffer,
			t_formatSpec *format,
			va_list *ap);

/* ============================ EXTENSIONS ============================ */

/**
 * @brief Handles repeat extension syntax: %R{count}{char}
 */
int		ft_printRepeat(t_printfBuffer *buffer,
			const char *format,
			size_t *i);

/**
 * @brief Handles pipe extension syntax:
 *
 * %|[pad][align]width[.precision]spec|
 */
int		ft_parsePipe(const char *format,
			size_t *i,
			t_formatSpec *fmt,
			va_list *ap);

/* ============================ ALIGNMENT & WIDTH ============================ */

/**
 * @brief Applies width padding to formatted content.
 */
int		ft_applyWidth(t_printfBuffer *buffer,
			t_formatSpec *format,
			char *content);

/**
 * @brief Applies alignment rules to formatted content.
 */
int		ft_applyAlignment(t_printfBuffer *buffer,
			t_formatSpec *format,
			char *content);

#endif
