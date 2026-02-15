/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hprintf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:53:40 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/15 21:50:19 by moutig           ###   ########.fr       */
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
	/* flags */
	int		leftAlign;
	int		centerAlign;
	int		zeroPad;

	/* width */
	int		width;

	/* precision */
	int		precision;
	int		hasPrecision;

	/* conversion */
	char	specifier;

	int		repeat;
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
 * @brief A printf-like function that formats and prints data to standard output.
 * You can use the following format specifiers:
 *  - %c: character
 *  - %s: string (null pointer prints "(null)")
 *  - %d/%i: signed integer with sign-aware zero padding
 *  - %%: literal '%'
 * Supports width, precision, left-align (-), center-align (_), zero-pad (0),
 * repeat (*N), and truncate (!).
 *
 * It must be ordered as follows: %[flags][width][.precision][!][*repeat]specifier
 * @param format - the format string
 * @param ... - variadic arguments corresponding to format specifiers
 * @return the total number of characters printed (not including null terminator)
 */
int		ft_printf(const char *format, ...);

/**
 * @brief A printf-like function that formats and prints data to a specified file descriptor.
 * Same format specifiers and features as ft_printf.
 * @param fd - file descriptor to write to
 * @param format - the format string
 * @param ... - variadic arguments corresponding to format specifiers
 * @return the total number of characters printed (not including null terminator)
 */
int		ft_dprintf(int fd, const char *format, ...);

/**
 * @brief A printf-like function that formats and prints data to standard output using a va_list.
 * Same format specifiers and features as ft_printf.
 * @param format - the format string
 * @param ap - va_list of arguments corresponding to format specifiers
 * @return the total number of characters printed (not including null terminator)
 */
int		ft_vprintf(const char *format, va_list ap);

/**
 * @brief A printf-like function that formats and prints data to a specified file descriptor using a va_list.
 * Same format specifiers and features as ft_printf.
 * @param fd - file descriptor to write to
 * @param format - the format string
 * @param ap - va_list of arguments corresponding to format specifiers
 * @return the total number of characters printed (not including null terminator)
 */
int		ft_vdprintf(int fd, const char *format, va_list ap);

/**
 * @brief A printf-like function that formats and writes data to a memory buffer.
 * Same format specifiers and features as ft_printf.
 * Writes at most size-1 characters to dst, null-terminating the result.
 * @param dst - destination buffer
 * @param size - size of the destination buffer
 * @param format - the format string
 * @param ... - variadic arguments corresponding to format specifiers
 * @return the total number of characters that would have been written if size were unlimited (not including null terminator)
 */
int		ft_snprintf(char		*dst,
					size_t		size,
					const char	*format,
					...);

/**
 * @brief A printf-like function that formats and writes data to a memory buffer using a va_list.
 * Same format specifiers and features as ft_printf.
 * Writes at most size-1 characters to dst, null-terminating the result.
 * @param dst - destination buffer
 * @param size - size of the destination buffer
 * @param format - the format string
 * @param ap - va_list of arguments corresponding to format specifiers
 * @return the total number of characters that would have been written if size were unlimited (not including null terminator)
 */
int		ft_vsnprintf(char		*dst,
					size_t		size,
					const char	*format,
					va_list		ap);

/* ============================ CORE ENGINE ============================ */

/**
 * @brief 
 * @param buffer - the printf buffer to write into
 * @param format - the format string
 * @param ap - the variadic arguments list
 * @return the total number of characters printed (not including null terminator), or -1 on error
 */
int		printfEngine(t_printfBuffer	*buffer,
					const char		*format,
					va_list			ap);

/* ============================ BUFFER MANAGEMENT ============================ */

/**
 * @brief Initializes a printfBuffer for writing to a file descriptor.
 * @param buffer - the printf buffer to initialize
 * @param fd - file descriptor to write to
 * @param mode - mode of operation (e.g., buffered or unbuffered)
 */
void	bufferInitFd(t_printfBuffer	*buffer,
					int				fd,
					int				mode);

/**
 * @brief Initializes a printfBuffer for writing to a memory buffer (snprintf mode).
 * @param buffer - the printf buffer to initialize
 * @param dst - destination buffer
 * @param size - size of the destination buffer
 */
void	bufferInitMemory(t_printfBuffer	*buffer,
						char			*dst,
						size_t			size);

/**
 * @brief Flushes the internal buffer to the output target (file descriptor or memory buffer).
 * @param buffer - the printf buffer to flush
 * @return 0 on success, -1 on error
 */
int		bufferFlush(t_printfBuffer *buffer);

/**
 * @brief Writes a single character to the printf buffer, handling buffering and output.
 * @param buffer - the printf buffer to write into
 * @param c - the character to write
 * @return 0 on success, -1 on error
 */
int		bufferPutChar(t_printfBuffer *buffer, char c);

/* ============================ PARSING ============================ */

/**
 * @brief Parses a format specification from the format string.
 * @param format - the full format string
 * @param i - pointer to current index in format (starts after '%')
 * @param spec - output struct to fill with parsed specifier details
 * @return 0 on success, -1 on error (e.g. invalid format)
 */
int parseFormat(const char *format, size_t *i, t_formatSpec *spec);

/**
 * @brief Resets a formatSpec struct to default values.
 * @param buffer - the printf buffer to write into
 * @param spec - the parsed format specification
 * @param ap - the variadic arguments list
 * @return 0 on success, -1 on error
 */
int dispatchFormat(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap);

/**
 * @brief Applies padding (spaces or zeros) based on the format specification and alignment.
 * @param buffer - the printf buffer to write into
 * @param spec - the parsed format specification
 * @param s - the string to format and emit
 * @param len - the length of the string s
 * @return 0 on success, -1 on error
 */
int emitFormatted(t_printfBuffer *buffer,
				t_formatSpec *spec,
				const char *s,
				size_t len);

/* ============================ HANDLERS ============================ */

int		handleInt(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap);
int		handleUnsigned(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap);
int		handleHex(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap);
int		handlePointer(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap);
int		handleFloat(t_printfBuffer *buffer, t_formatSpec *spec, va_list ap);

#endif
