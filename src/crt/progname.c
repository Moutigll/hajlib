/**
 * @file progname.c
 * @brief Storage for the program name (argv[0]).
 *
 * The CRT startup code (_start) stores argv[0] here so that
 * diagnostic functions (like __assert_fail) can print the
 * program name.
 *
 * __progname is a BSD convention, also used by musl, FreeBSD,
 * and macOS. It is declared in <bits/crt.h>.
 */

#include <bits/crt.h>

const char	*__progname = "(program)";
