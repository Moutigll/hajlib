/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/*
 * _start - FreeBSD aarch64 entry point.
 *
 * FreeBSD and Linux share the AAPCS64 ABI on aarch64. The initial
 * stack layout is also the same. This file is therefore almost
 * identical to the Linux aarch64 version.
 *
 * Do not DRY this out. Keeping per-OS files makes future
 * modifications easier.
 */

.text
.global _start
.type   _start, %function

_start:
	ldr	x0, [sp]		/* argc */
	add	x1, sp, #8		/* argv */

	ldr	x3, [x1]			/* x3 = argv[0] */
	adrp	x4, __progname			/* x4 = page of __progname */
	add	x4, x4, :lo12:__progname	/* x4 = address of __progname */
	str	x3, [x4]			/* __progname = argv[0] */

	add	x2, x1, x0, lsl #3	/* envp = argv + argc*8 */
	add	x2, x2, #8		/* + 1 for NULL */

	and	sp, sp, #-16		/* align stack */

	bl	main			/* main(argc, argv, envp) */

	bl	exit			/* exit(main_return_value) */

1:
	wfe
	b	1b

.size	_start, .-_start
