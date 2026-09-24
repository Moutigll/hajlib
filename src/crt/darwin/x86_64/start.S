/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/*
 * start - Darwin x86_64 entry point.
 *
 * DIFFERENCES FROM LINUX x86_64
 *
 *   1. The symbol is `start`, NOT `_start`. The Darwin linker
 *      looks for this exact name.
 *
 *   2. The kernel does NOT use the stack to pass argc/argv/envp.
 *      It uses the REGISTERS:
 *        rdi = argc
 *        rsi = argv
 *        rdx = envp
 *      So we do not need to read from the stack at all.
 *
 *   3. The ABI is still System V AMD64, so the calling convention
 *      for main() is the same.
 *
 *   4. The safety net uses `hlt`, which on Darwin also raises a
 *      signal in user mode.
 *
 * WHY THE REGISTERS ARE USED
 *
 * Darwin's kernel (XNU) sets up the initial state differently
 * from Linux. At the entry point, it has already loaded argc,
 * argv, and envp into registers, presumably for efficiency. The
 * stack is not used for this purpose.
 */

.text
.global start
.type   start, @function

start:
	/*
	 * The registers already contain what we need:
	 *   rdi = argc
	 *   rsi = argv
	 *   rdx = envp
	 *
	 * Store argv[0] into __progname.
	 *
	 * __progname is a global variable defined in src/crt/progname.c.
	 * It holds the program name (argv[0]) so that diagnostic
	 * functions like __assert_fail can print it.
	 *
	 * On Darwin, the C symbol __progname becomes ___progname
	 * (three underscores) in the assembly file, because the
	 * assembler adds an extra underscore to every C symbol.
	 *
	 * rsi points to argv, so (%rsi) is argv[0].
	 */
	movq	(%rsi), %rax		/* rax = argv[0] */
	movq	%rax, ___progname(%rip)	/* __progname = argv[0] */

	/*
	 * We could call main directly, but we still want to align
	 * the stack defensively.
	 */
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

.size	start, .-start
