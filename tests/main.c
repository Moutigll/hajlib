/*
 * hajlib - A POSIX-like C library.
 * SPDX-License-Identifier: MIT
 *
 * main.c - minimal test program.
 *
 * This program prints the hajlib version and a small message.
 * It is used to verify that the library links and runs.
 */

#include <haj/version.h>

#include <bits/syscall.h>

/*
 * We do not have write() or printf() implemented yet, so we use
 * the raw syscall for output.
 */
long	__haj_syscall6(long nr, long a1, long a2, long a3,
                       long a4, long a5, long a6);

/* --------------------------------------------------------------------------
 * Minimal output
 * -------------------------------------------------------------------------- */

static void	putstr(const char *s)
{
	unsigned long	len = 0;

	while (s[len])
		len++;
	if (len > 0)
		__haj_syscall6(SYS_write, 1, (long)s, (long)len, 0, 0, 0);
}

/* --------------------------------------------------------------------------
 * Main
 * -------------------------------------------------------------------------- */

int	main(void)
{
	putstr("hajlib version: ");
	putstr(HAJ_VERSION_STRING);
	putstr("\n");

	putstr("Hello from hajlib!\n");

	return (0);
}
