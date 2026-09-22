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

	and	sp, sp, #-16		/* align stack */

	bl	main			/* main(argc, argv, envp) */

	bl	exit			/* exit(main_return_value) */

1:
	wfe
	b	1b

.size	start, .-start
