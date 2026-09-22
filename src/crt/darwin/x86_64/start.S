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
