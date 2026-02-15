/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 17:35:44 by moutig            #+#    #+#             */
/*   Updated: 2026/02/15 15:23:03 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/hprintf.h"
#include <stddef.h>

static void
initFormatSpec(t_formatSpec *spec)
{
	spec->leftAlign = 0;
	spec->centerAlign = 0;
	spec->zeroPad = 0;
	spec->width = 0;
	spec->precision = 0;
	spec->hasPrecision = 0;
	spec->specifier = 0;
	spec->repeat = 1;
	spec->truncate = 0;
}

/**
 * @brief Parse flags from the format string starting at format[*i].
 * @param format - the full format string
 * @param i - pointer to current index in format (starts after '%')
 * @param spec - output struct to fill with parsed specifier details
 */
static void
parseFlags(const char *format, size_t *i, t_formatSpec *spec)
{
	while (format[*i] == '-' || format[*i] == '_' || format[*i] == '0')
	{
		if (format[*i] == '-')
			spec->leftAlign = 1;
		else if (format[*i] == '_')
			spec->centerAlign = 1;
		else if (format[*i] == '0')
			spec->zeroPad = 1;
		(*i)++;
	}
	/* normalize: leftAlign overrides zeroPad, center overrides left */
	if (spec->leftAlign)
		spec->zeroPad = 0;
	if (spec->centerAlign)
	{
		spec->leftAlign = 0;
		spec->zeroPad = 0;
	}
}

static int
parseNumber(const char *format, size_t *i)
{
	int value;

	value = 0;
	while (format[*i] >= '0' && format[*i] <= '9')
	{
		value = value * 10 + (format[*i] - '0');
		(*i)++;
	}
	return (value);
}

/**
 * @brief Parse a single format starting at format[*i] (after '%').
 *
 * Fills spec and advances *i to the character after the specifier.
 * Returns 0 on success, -1 on malformed (e.g. end of string).
 *
 * Syntax supported:
 *  %[flags][- _ 0][width][.precision][!][*repeat]specifier
 *
 * Example: "%_10.5!*3s" => center, width=10, precision=5, truncate=1, repeat=3, spec='s'
 */
int
parseFormat(const char *format, size_t *i, t_formatSpec *spec)
{
	initFormatSpec(spec);
	parseFlags(format, i, spec);
	if (format[*i] >= '0' && format[*i] <= '9') /* parse width if present */
		spec->width = parseNumber(format, i);
	if (format[*i] == '.') /* parse precision if present */
	{
		(*i)++;
		spec->hasPrecision = 1;
		if (format[*i] >= '0' && format[*i] <= '9')
			spec->precision = parseNumber(format, i);
		else
			spec->precision = 0; /* treat '.' with no number as precision 0 */
	}
	if (format[*i] == '!') /* parse truncate flag if present */
	{
		spec->truncate = 1;
			(*i)++;
		}
	if (format[*i] == '*') /* parse repeat if present */
	{
		(*i)++;
		spec->repeat = parseNumber(format, i);
		if (spec->repeat <= 0)
			spec->repeat = 1; /* treat non-positive repeat as 1 */
	}
	if (format[*i] == '\0')
		return (-1);
	spec->specifier = format[*i];
	(*i)++;
	return (0);
}
