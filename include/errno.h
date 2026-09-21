/**
 * @file errno.h
 * @brief Error reporting.
 *
 * This header defines the errno macro and the error codes
 * (EPERM, ENOENT, ...). The errno value is thread-local on all
 * supported platforms.
 *
 * The error codes themselves are defined in <bits/errno.h>
 * with per-OS values.
 */

#ifndef _ERRNO_H
# define _ERRNO_H

# include <bits/errno.h>

/*
 * errno
 * -----
 *
 * The errno macro expands to a thread-local lvalue of type int.
 * Functions set errno on failure; user code reads it.
 *
 * In a libc replacement, errno must be thread-local. We use the
 * compiler's TLS support (__thread on GCC/Clang, __declspec(thread)
 * on MSVC) to declare it.
 *
 * The actual storage is defined in src/errno/errno.c.
 */

# if defined(__cplusplus)
extern "C" {
# endif

extern __thread int	__haj_errno;

# if defined(__cplusplus)
}
# endif

# ifndef errno
#  define errno	__haj_errno
# endif

#endif /* _ERRNO_H */
