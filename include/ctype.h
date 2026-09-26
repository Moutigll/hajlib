/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/**
 * @file ctype.h
 * @brief C standard character classification and conversion functions.
 * @Created: 2026/09/26 02:43:58 by Moutig
 * @Updated: 2026/09/26 03:23:30 by Moutig
 *
 * ASCII-only implementation for the "C" locale. The functions
 * accept an int whose value must be representable as unsigned
 * char or equal to EOF. Passing a negative value other than EOF
 * is undefined behavior (as per the C standard).
 *
 * All classification functions return 0 for EOF. tolower and
 * toupper return c unchanged for EOF or non-letter bytes.
 */

#ifndef _CTYPE_H
# define _CTYPE_H

# include <bits/compiler.h>

# ifdef __cplusplus
extern "C" {
# endif

/* End-of-file constant (also defined in <stdio.h>). */
# ifndef EOF
#  define EOF (-1)
# endif

/* ----- Classification (ASCII / "C" locale) ----- */

/**
 * @brief Check if the character is a digit (0-9).
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is a digit, 0 otherwise.
 */
static inline int isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Check if the character is a lowercase letter.
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is a lowercase letter, 0 otherwise.
 */
static inline int islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

/**
 * @brief Check if the character is an uppercase letter.
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is an uppercase letter, 0 otherwise.
 */
static inline int isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

/**
 * @brief Check if the character is an alphabetic letter.
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is an alphabetic letter, 0 otherwise.
 */
static inline int isalpha(int c)
{
	return (isupper(c) || islower(c));
}

/**
 * @brief Check if the character is alphanumeric (letter or digit).
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is alphanumeric, 0 otherwise.
 */
static inline int isalnum(int c)
{
	return (isalpha(c) || isdigit(c));
}

/**
 * @brief Check if the character is a blank character (space or tab).
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is a blank character, 0 otherwise.
 */
static inline int isblank(int c)
{
	return (c == ' ' || c == '\t');
}

/**
 * @brief Check if the character is a control character.
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is a control character, 0 otherwise.
 */
static inline int iscntrl(int c)
{
	unsigned int b = (unsigned int)(unsigned char)c;
	return (b < 0x20 || b == 0x7F);
}

/**
 * @brief Check if the character is a graphical character (printable and not space).
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is a graphical character, 0 otherwise.
 */
static inline int isgraph(int c)
{
	unsigned int b = (unsigned int)(unsigned char)c;
	return (b > 0x20 && b < 0x7F);
}

/**
 * @brief Check if the character is a printable character.
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is a printable character, 0 otherwise.
 */
static inline int isprint(int c)
{
	unsigned int b = (unsigned int)(unsigned char)c;
	return (b >= 0x20 && b < 0x7F);
}

/**
 * @brief Check if the character is a punctuation character.
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is a punctuation character, 0 otherwise.
 */
static inline int ispunct(int c)
{
	return (isgraph(c) && !isalnum(c));
}

/**
 * @brief Check if the character is a whitespace character.
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is a whitespace character, 0 otherwise.
 */
static inline int isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r');
}

/**
 * @brief Check if the character is a hexadecimal digit (0-9, a-f, A-F).
 * @param c Character to check (must be representable as unsigned char or EOF).
 * @return Non-zero if c is a hexadecimal digit, 0 otherwise.
 */
static inline int isxdigit(int c)
{
	return (isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

/* ----- Conversion (ASCII / "C" locale) ----- */

/**
 * @brief Convert the character to lowercase if it is an uppercase letter.
 * @param c Character to convert (must be representable as unsigned char or EOF).
 * @return The lowercase equivalent of c if it is an uppercase letter, otherwise c unchanged.
 */
static inline int tolower(int c)
{
	return ((c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c);
}
/**
 * @brief Convert the character to uppercase if it is a lowercase letter.
 * @param c Character to convert (must be representable as unsigned char or EOF).
 * @return The uppercase equivalent of c if it is a lowercase letter, otherwise c unchanged.
 */
static inline int toupper(int c)
{
	return ((c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c);
}

# ifdef __cplusplus
}
# endif

#endif /* _CTYPE_H */
