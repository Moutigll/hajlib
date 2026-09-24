/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/**
 * @file progname.c
 * @brief Storage for the program name (argv[0]).
 * @Created: 2026/09/24 15:06:42 by Moutig
 * @Updated: 2026/09/24 18:26:47 by Moutig
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
