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
 * @Updated: 2026/09/24 22:20:49 by Moutig
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

# if defined(__cplusplus)
}
# endif

#endif /* _STRING_H */
