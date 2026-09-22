/**
 * @file _exit.c
 * @brief Implementation of _exit().
 *
 * _exit() terminates the process immediately, without running
 * atexit handlers or flushing stdio buffers. This is the
 * "raw" termination, used by exit() after it has done its job.
 *
 * On Linux, we use the exit_group syscall, which terminates all
 * threads in the process. On other OSes, we use the appropriate
 * exit syscall.
 */

#include <unistd.h>
#include <bits/syscall.h>

__HAJ_NORETURN
void	_exit(int status)
{
#if defined(HAJ_OS_LINUX)
	/*
	 * exit_group terminates all threads, not just the calling
	 * one. This is the correct behavior for a process-wide
	 * exit.
	 */
	__haj_syscall6(SYS_exit_group, status, 0, 0, 0, 0, 0);
#else
	/*
	 * On other OSes, exit terminates the process. There is no
	 * distinction between "exit this thread" and "exit the
	 * process" in the base syscall.
	 */
	__haj_syscall6(SYS_exit, status, 0, 0, 0, 0, 0);
#endif

	/*
	 * The syscall should never return. If it does (e.g. if the
	 * syscall number is wrong), we loop forever to avoid
	 * undefined behavior.
	 */
	for (;;) {
	}
}
