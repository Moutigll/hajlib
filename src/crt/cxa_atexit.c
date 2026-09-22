/**
 * @file cxa_atexit.c
 * @brief Implementation of __cxa_atexit.
 *
 * __cxa_atexit is the C++ ABI function for registering
 * destructors that should run at exit. It is also used by GCC
 * for __attribute__((destructor)) on C code compiled with
 * certain flags.
 *
 * The signature is:
 *   int __cxa_atexit(void (*func)(void *), void *arg, void *dso_handle);
 *
 * We do not support the dso_handle for now. We just call func
 * with arg when the process exits.
 */

#include <stdlib.h>
#include <stddef.h>

#include <bits/crt.h>

#define HAJ_CXA_ATEXIT_MAX	32

struct cxa_atexit_entry {
	void	(*func)(void *);
	void	*arg;
};

static struct cxa_atexit_entry	g_cxa_handlers[HAJ_CXA_ATEXIT_MAX];
static int						g_cxa_count = 0;

int	__cxa_atexit(void (*func)(void *), void *arg, void *dso_handle)
{
	(void)dso_handle;

	if (func == NULL)
		return (-1);
	if (g_cxa_count >= HAJ_CXA_ATEXIT_MAX)
		return (-1);

	g_cxa_handlers[g_cxa_count].func = func;
	g_cxa_handlers[g_cxa_count].arg = arg;
	g_cxa_count++;
	return (0);
}

/*
 * Called by __cxa_finalize with NULL to run all handlers.
 * This is what exit() would call if it supported C++ destruction.
 * For now, this is a no-op until we integrate it into exit().
 */
void	__haj_run_cxa_atexit(void)
{
	while (g_cxa_count > 0) {
		g_cxa_count--;
		g_cxa_handlers[g_cxa_count].func(
			g_cxa_handlers[g_cxa_count].arg);
	}
}
