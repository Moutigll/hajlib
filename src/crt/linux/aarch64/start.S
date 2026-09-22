/*
 * _start - Linux aarch64 entry point.
 *
 * This file is the aarch64 equivalent of the x86_64 version.
 *
 * DIFFERENCES FROM x86_64
 *
 *   1. Registers are named x0-x30 (64-bit). w0-w30 are the
 *      32-bit views.
 *   2. The syscall instruction is `svc #0` (Supervisor Call),
 *      not `syscall`.
 *   3. Function arguments are passed in x0-x7 (up to 8 args),
 *      not rdi, rsi, rdx, rcx, r8, r9.
 *   4. The return address is in x30 (link register), not on
 *      the stack. `bl` (Branch with Link) stores the return
 *      address in x30.
 *   5. The stack pointer is `sp`, not `rsp`. It must be
 *      16-byte aligned at all times.
 *   6. The kernel does NOT pass argc in a register. It is on
 *      the stack, at [sp].
 *
 * REGISTERS (aarch64)
 *
 *   x0-x7  : function arguments and return value
 *   x8     : syscall number (indirect result register)
 *   x9-x15 : temporary, caller-saved
 *   x16-x17: intra-procedure call scratch
 *   x18    : platform register (reserved on some systems)
 *   x19-x28: callee-saved
 *   x29    : frame pointer (fp)
 *   x30    : link register (lr, return address)
 *   sp     : stack pointer
 *   pc     : program counter (not directly accessible)
 *
 * The stack at entry as the same layout as x86_64, except that the pointers are 8 bytes each (64-bit).
 */

.text
.global _start
.type   _start, %function

_start:
	/*
	 * Load argc from [sp].
	 *
	 * `ldr x0, [sp]` loads the 8 bytes at the address in sp into
	 * x0. x0 is the 1st argument register for function calls.
	 *
	 * After: x0 = argc
	 */
	ldr	x0, [sp]

	/*
	 * Compute argv = sp + 8.
	 *
	 * `add x1, sp, #8` adds 8 to sp and stores the result in x1.
	 * x1 is the 2nd argument register.
	 *
	 * After: x1 = address of argv[0]
	 */
	add	x1, sp, #8

	/*
	 * Compute envp = argv + (argc + 1) * 8.
	 *
	 * `add x2, x1, x0, lsl #3` adds x1 to (x0 << 3) and stores
	 * in x2. `lsl #3` is "logical shift left by 3", equivalent
	 * to multiplying by 8.
	 *
	 * Then `add x2, x2, #8` adds 8 to skip the NULL terminator.
	 *
	 * After: x2 = address of envp[0]
	 */
	add	x2, x1, x0, lsl #3
	add	x2, x2, #8

	/*
	 * Align the stack to 16 bytes.
	 *
	 * `and sp, sp, #-16` masks the low 4 bits of sp to 0.
	 *
	 * Note: aarch64 requires 16-byte alignment for SP at all
	 * times. The kernel already guarantees this at _start entry,
	 * so this is defensive.
	 */
	and	sp, sp, #-16

	/*
	 * Call main.
	 *
	 * `bl main` (Branch with Link) does two things:
	 *   1. Stores the address of the next instruction in x30.
	 *   2. Jumps to main.
	 *
	 * main receives:
	 *   x0 = argc
	 *   x1 = argv
	 *   x2 = envp
	 *
	 * main returns its value in x0.
	 */
	bl	main

	/*
	 * Call exit(main_return_value).
	 *
	 * x0 already contains main's return value, which is exactly
	 * what exit expects as its 1st argument. No move needed.
	 */
	bl	exit

	/*
	 * Safety net.
	 *
	 * `wfe` (Wait For Event) is a low-power hint. In user mode,
	 * it may be a no-op. The infinite loop prevents falling off
	 * the end of the function.
	 */
1:
	wfe
	b	1b

.size	_start, .-_start
