#ifndef MALLOC_OS_H
# define MALLOC_OS_H

# include <stddef.h>

# if defined(_WIN32) || defined(WIN32)
#  include <windows.h>
#  define HMALLOC_THREAD_LOCAL __declspec(thread)
# else
#  include <sys/mman.h>
#  include <unistd.h>
#  include <pthread.h>
#  define HMALLOC_THREAD_LOCAL __thread
# endif

static inline size_t	hmallocPagesize(void)
{
# if defined(_WIN32) || defined(WIN32)
	SYSTEM_INFO	si;
	GetSystemInfo(&si);
	return ((size_t)si.dwPageSize);
# else
	return ((size_t)getpagesize());
# endif
}

static inline void	*hmallocMap(size_t size)
{
# if defined(_WIN32) || defined(WIN32)
	return (VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT,
			PAGE_READWRITE));
# else
	void	*p;

	/* Create a new memory zone with
	 * Protections:
	 * - Read to allow reading from the memory region.
	 * - Write to allow writing to the memory region.
	 * Flags:
	 * - MAP_PRIVATE to create a private mapping that is not shared with other processes.
	 * - MAP_ANONYMOUS to create an anonymous mapping that is not backed by any file.
	 */
	p = mmap(NULL, size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (p == MAP_FAILED)
		return (NULL);
	return (p);
# endif
}

static inline void	hmallocUnmap(void *ptr, size_t size)
{
	if (!ptr)
		return;
# if defined(_WIN32) || defined(WIN32)
	(void)size;
	VirtualFree(ptr, 0, MEM_RELEASE);
# else
	munmap(ptr, size);
# endif
}

#if defined(_WIN32) || defined(WIN32)
	typedef SRWLOCK hmallocMutex_t;
	#define hmallocMutexInit(m)			InitializeSRWLock(m)
	#define hmallocMutexLock(m)			AcquireSRWLockExclusive(m)
	#define hmallocMutexUnlock(m)		ReleaseSRWLockExclusive(m)
	#define HMALLOC_MUTEX_INITIALIZER	SRWLOCK_INIT
#else
	typedef pthread_mutex_t hmallocMutex_t;
	#define hmallocMutexInit(m)			pthread_mutex_init(m, NULL)
	#define hmallocMutexLock(m)			pthread_mutex_lock(m)
	#define hmallocMutexUnlock(m)		pthread_mutex_unlock(m)
	#define HMALLOC_MUTEX_INITIALIZER	PTHREAD_MUTEX_INITIALIZER
#endif

#endif
