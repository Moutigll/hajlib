/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/*
 * _start - FreeBSD x86_64 entry point.
 * It's the same as Linux x86_64 but we keep it separate for clarity and future FreeBSD-specific changes.
 */

.text
.global _start
.type   _start, @function

_start:
	/* argc = *(long *)rsp */
	movq	(%rsp), %rdi

	/* argv = rsp + 8 */
	leaq	8(%rsp), %rsi

	movq	(%rsi), %rax		/* rax = argv[0] */
	movq	%rax, __progname(%rip)	/* __progname = argv[0] */

	/* envp = argv + (argc + 1) * 8 */
	leaq	8(%rsi,%rdi,8), %rdx

	/* Align stack to 16 bytes. */
	andq	$-16, %rsp

	/* Call main(argc, argv, envp). */
	call	main

	/* Call exit(main_return_value). */
	movq	%rax, %rdi
	call	exit

	/* Safety net. */
1:
	hlt
	jmp	1b

.size	_start, .-_start
