/**
 * @file open.c
 * @brief Implementation of open().
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
