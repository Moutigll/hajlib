/**
 * @file abort.c
 * @brief Implementation of abort().
 *
 * abort() raises SIGABRT and terminates the process. We do not
 * have signal support yet, so we do the syscall directly with
 * the exit status 128 + SIGABRT (134).
 */

#include <stdlib.h>
#include <bits/syscall.h>

__HAJ_NORETURN
void	abort(void)
{
	/**
	 * @TODO: add sigabrt
	 * In a full implementation, this would raise SIGABRT and
	 * let the handler (if any) run. Since we do not have
	 * signals, we just terminate with the status that a shell
	 * would report for SIGABRT.
	 */
	__haj_syscall6(SYS_exit_group, 134, 0, 0, 0, 0, 0);
	for (;;) {
	}
}
