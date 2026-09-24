/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/**
 * @file open.c
 * @brief Implementation of open().
 * @Created: 2026/09/24 15:06:42 by Moutig
 * @Updated: 2026/09/24 18:29:35 by Moutig
 *
 * open() opens or creates a file and returns a file descriptor.
 * It is a variadic function: the third argument (mode) is only
 * present if O_CREAT or O_TMPFILE is set in flags. The mode
 * argument is ignored if the file already exists.
 */

#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>

#include <bits/syscall.h>

/**
 * @brief Open or create a file.
 *
 * On Linux, we use the openat syscall with AT_FDCWD as the
 * directory file descriptor, because the raw open syscall is
 * not available on all architectures (aarch64 only has openat).
 */
int	open(const char *path, int flags, ...)
{
	mode_t	mode = 0;
	long	ret;

	/*
	 * The mode argument is only present if O_CREAT or O_TMPFILE
	 * is set. Reading it unconditionally would be undefined
	 * behavior.
	 */
#if defined(O_TMPFILE)
	if (flags & (O_CREAT | O_TMPFILE)) {
#else
	if (flags & O_CREAT) {
#endif
		va_list	ap;

		va_start(ap, flags);
		mode = (mode_t)va_arg(ap, int);
		va_end(ap);
	}

	/* We use the openat syscall since open is not available on all architectures. */
	ret = __haj_syscall6(SYS_openat,
	                     AT_FDCWD,
	                     (long)path,
	                     flags,
	                     (long)mode,
	                     0, 0);

	if (ret < 0 && ret >= -4095) {
		errno = (int)-ret;
		return (-1);
	}

	return ((int)ret);
}
