/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/**
 * @file string.h
 * @brief C standard string and memory functions.
 * @Created: 2026/09/24 22:10:46 by Moutig
 * @Updated: 2026/09/25 23:23:20 by Moutig
 *
 * This header declares the C standard string and memory
 * functions, plus a few POSIX/GNU extensions (memrchr, strdup,
 * strndup, strtok_r, strcasestr, bzero, bcopy, stpcpy, stpncpy).
 */

#ifndef _STRING_H
# define _STRING_H

# include <bits/compiler.h>
# include <sys/types.h>	/* size_t */

# if defined(__cplusplus)
extern "C" {
# endif

/* ----- Memory operations ----- */

/**
 * @brief Copy n bytes from src to dest. Regions must not overlap.
 *
 * @param dest Destination buffer.
 * @param src  Source buffer.
 * @param n    Number of bytes to copy.
 * @return dest.
 */
void	*memcpy(void *__HAJ_RESTRICT dest, const void *__HAJ_RESTRICT src, size_t n);

/**
 * @brief Copy n bytes from src to dest. Regions may overlap.
 *
 * @param dest Destination buffer.
 * @param src  Source buffer.
 * @param n    Number of bytes to copy.
 * @return dest.
 */
void	*memmove(void *dest, const void *src, size_t n);

/**
 * @brief Fill the first n bytes of the memory area pointed to by s with the constant byte c.
 *
 * @param s Pointer to the memory area to fill.
 * @param c Byte value to set (converted to unsigned char).
 * @param n Number of bytes to fill.
 * @return s.
 */
void	*memset(void *s, int c, size_t n);

#if defined(__HAJ_SOURCE)
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)	/* Fill memory with zero bytes. */
#endif

/**
 * @brief Compare the first n bytes of two memory areas.
 *
 * @param s1 Pointer to the first memory area.
 * @param s2 Pointer to the second memory area.
 * @param n  Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if the first n bytes of s1 is found,
 *         respectively, to be less than, to match, or be greater than the first n bytes of s2.
 */
int		memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Locate the first occurrence of c (converted to an unsigned char) in the first n bytes of s.
 *
 * Each byte is interpreted as an unsigned char.
 * The function returns a pointer to the matching byte or NULL if the character does not occur in the given memory area.
 * @param s Pointer to the memory area to search.
 * @param c Byte value to search for (converted to unsigned char).
 * @param n Number of bytes to search.
 * @return A pointer to the matching byte or NULL if the character does not occur in the given memory area.
 */
void	*memchr(const void *s, int c, size_t n);

#if defined(__HAJ_SOURCE)
/**
 * @brief Locate the last occurrence of c (converted to an unsigned char) in the first n bytes of s.
 *
 * Each byte is interpreted as an unsigned char.
 * The function returns a pointer to the matching byte or NULL if the character does not occur in the given memory area.
 * @param s Pointer to the memory area to search.
 * @param c Byte value to search for (converted to unsigned char).
 * @param n Number of bytes to search.
 * @return A pointer to the matching byte or NULL if the character does not occur in the given memory area.
 */
void	*memrchr(const void *s, int c, size_t n);
#endif

/**
 * @brief Copy bytes from src to dest until the character c (converted to an unsigned char) is found.
 *
 * The function copies bytes from src to dest until it encounters the character c (converted to an unsigned char) or reaches n bytes.
 * @param dest Destination buffer.
 * @param src  Source buffer.
 * @param c    Character to stop copying at (converted to an unsigned char).
 * @param n    Maximum number of bytes to copy.
 * @return A pointer to the byte after the first occurrence of c in the copied data, or NULL if c is not found within n bytes.
 */
void	*memccpy(void *__HAJ_RESTRICT dest, const void *__HAJ_RESTRICT src, int c, size_t n);



/* ----- String operations ----- */

/**
 * @brief Calculate the length of a null-terminated string.
 *
 * The function computes the length of the string s, excluding the terminating null byte ('\0').
 * @param s Pointer to the null-terminated string.
 * @return The number of characters in the string, excluding the null terminator.
 */
size_t	strlen(const char *s);

/**
 * @brief Calculate the length of a null-terminated string, up to a maximum of maxlen bytes.
 *
 * The function computes the length of the string s, excluding the terminating null byte ('\0'),
 * but at most maxlen bytes are examined.
 * @param s Pointer to the null-terminated string.
 * @param maxlen Maximum number of bytes to examine.
 * @return The number of characters in the string, excluding the null terminator, but at most maxlen.
 */
size_t	strnlen(const char *s, size_t maxlen);

# if defined(__cplusplus)
}
# endif

#endif /* _STRING_H */
