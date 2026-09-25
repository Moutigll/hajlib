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
 * @Updated: 2026/09/25 22:04:13 by Moutig
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

# if defined(__cplusplus)
}
# endif

#endif /* _STRING_H */
