/*
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright (C) 2026 Moutig <ele-lean@moutig.sh>
 *
 * This file is part of hajlib.
 * See LICENSE for the full license text.
 */

/**
 * @file stack_chk_guard.c
 * @brief Definition of __stack_chk_guard.
 * @Created: 2026/09/24 15:06:42 by Moutig
 * @Updated: 2026/09/24 18:31:35 by Moutig
 *
 * WHAT IS THE STACK GUARD ?
 *
 * When compiled with -fstack-protector (or -fstack-protector-strong,
 * or -fstack-protector-all), the compiler inserts a "canary"
 * value on the stack, between the local variables and the saved
 * return address:
 *
 *   +-------------------------+  <- high address
 *   | saved return address    |
 *   +-------------------------+
 *   | saved rbp / frame ptr   |
 *   +-------------------------+
 *   | __stack_chk_guard value |  <- the canary
 *   +-------------------------+
 *   | local variables         |
 *   +-------------------------+  <- rsp
 *
 * Before returning from the function, the compiler compares the
 * value on the stack with __stack_chk_guard. If they differ, a
 * buffer overflow has occurred (the canary was overwritten), and
 * the compiler calls __stack_chk_fail().
 *
 * WHY THREAD-LOCAL ?
 *
 * On a system with threads, each thread must have its own canary,
 * because a thread could be reading the canary while another
 * thread is writing it. Thread-local storage (TLS) guarantees
 * that each thread has its own copy.
 *
 * On a system without threads, a plain global works.
 *
 * We use the __HAJ_THREAD_LOCAL macro defined in bits/compiler.h.
 * If threads are not supported, the macro expands to nothing and
 * __stack_chk_guard is a plain global.
 *
 * INITIALIZATION
 *
 * The canary must be initialized with a random value at program
 * startup. If it is always 0 (or any fixed value), an attacker
 * can easily guess it and bypass the protection.
 *
 * The initialization is done by the C runtime (__haj_init_guard,
 * called from _start or from a constructor). For now, we
 * initialize it to a fixed value. This is NOT SECURE, but it
 * works for testing.
 *
 * A proper implementation would call getrandom() or read from
 * /dev/urandom at startup.
 */

#include <bits/os.h>
#include <bits/compiler.h>
#include <bits/types.h>

/* Forward declaration to avoid warnings */
void __haj_init_stack_guard(void);

/**
 * @brief The stack canary value.
 *
 * This variable is used by the compiler to detect stack
 * corruption. It is initialized at program startup with a
 * random value.
 *
 * On a system with threads, this variable is thread-local: each
 * thread has its own copy. On a single-threaded system, it is a
 * plain global.
 */
__HAJ_THREAD_LOCAL __haj_uintptr	__stack_chk_guard = 0;

/**
 * @brief Initialize the stack canary.
 *
 * This function initializes the stack canary with a random value.
 * It should be called at program startup.
 */
void	__haj_init_stack_guard(void)
{
	/**
	 * Placeholder: use a fixed value.
	 * @TODO: replace with a random value from getrandom() or /dev/urandom.
	 * A real implementation would do:
	 *
	 *   unsigned long seed;
	 *   getrandom(&seed, sizeof(seed), 0);
	 *   __stack_chk_guard = seed;
	 *   __stack_chk_guard &= ~(unsigned long)0xFF;  // low byte = 0
	 *
	 * The low byte is set to 0 so that the canary contains a
	 * NUL byte, which stops string-based overflows from
	 * copying it.
	 */
	__stack_chk_guard = (__haj_uintptr)0xDEADBEEFCAFEBABEULL;
	__stack_chk_guard &= ~(__haj_uintptr)0xFF;
}
