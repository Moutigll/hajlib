/**
 * @file errno.c
 * @brief Storage for the errno variable.
 *
 * This file defines the thread-local errno variable declared in
 * <errno.h>. It must be compiled once and linked into the library.
 */

#include <errno.h>

__thread int	__haj_errno = 0;
