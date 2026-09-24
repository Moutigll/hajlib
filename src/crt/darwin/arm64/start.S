/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/*
 * start - Darwin arm64 entry point.
 *
 * DIFFERENCES FROM LINUX aarch64
 *
 *   1. The symbol is `start`, not `_start`.
 *
 *   2. The kernel passes argc/argv/envp in registers:
 *        x0 = argc
 *        x1 = argv
 *        x2 = envp
 *
 *   3. The rest is identical: AAPCS64 calling convention, 16-byte
 *      stack alignment, `bl` for function calls, `wfe` for the
 *      safety net.
 */

.text
.global start
.type   start, %function

start:
	/* x0, x1, x2 already contain argc, argv, envp. */
	/* Load argv[0] into x3 and store it in __progname. */
	ldr	x3, [x1]			/* x3 = argv[0] */
	adrp	x4, ___progname			/* x4 = page of __progname */
	add	x4, x4, :lo12:___progname	/* x4 = address of __progname */
	str	x3, [x4]			/* __progname = argv[0] */

	and	sp, sp, #-16		/* align stack */

	bl	main			/* main(argc, argv, envp) */

	bl	exit			/* exit(main_return_value) */

1:
	wfe
	b	1b

.size	start, .-start
