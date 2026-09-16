#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define WARMUP_ITERS	10000
#define BENCH_ITERS		200000
#define MAX_LIVE		4096
#define NUM_THREADS		4
#define THREAD_ITERS	100000

static const size_t g_sizes[] = {
	8, 16, 24, 32, 48, 64, 96, 128,	/* tiny  */
	256, 512, 1024, 2048, 4096,				/* small */
	8192, 16384, 65536, 262144					/* large */
};
#define NUM_SIZES (sizeof(g_sizes) / sizeof(g_sizes[0]))


static double nowSec(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (double)(ts.tv_sec + ts.tv_nsec * 1e-9);
}

/**
 * Compilation barrier : avoid the compiler to optimize away the pointer p and the memory accesses before it.
 * This is used to prevent the compiler from optimizing away the malloc/free calls and the memory accesses
 */
static inline void compilerBarrier(void *p)
{
	__asm__ __volatile__("" : : "r"(p) : "memory");
}

/**
 * Read a byte from the pointer p in a volatile way to prevent the compiler from optimizing away the read.
 * This is used to prevent the compiler from optimizing away the memory accesses and to ensure that the memory is actually read.
 */
static inline unsigned char touchRead(const void *p)
{
	return (*(volatile const unsigned char *)p);
}

/**
 * Global sink variable to prevent the compiler from optimizing away the results of the benchmarks.
 * This variable is used to store the result of the memory accesses in the benchmarks, so that the compiler cannot optimize away the memory accesses.
 */
static volatile void *g_sink;

/* Simple PRNG (xorshift64) */

static uint64_t g_rngState = 0x123456789abcdef0ULL;

static uint64_t rngNext(void)
{
	uint64_t x = g_rngState;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	g_rngState = x;
	return (x);
}

static size_t rngRange(size_t n)
{
	return ((size_t)(rngNext() % n));
}

/*
 * Parseable output format for compare.py :
 *   <key> <iters> <totalSeconds> <nsPerOp>
 */
static void printHeader(const char *name)
{
	printf("\n=== %s ===\n", name);
	printf("%-12s %-12s %-14s %-14s\n",
		   "key", "iters", "total(s)", "ns/op");
}

static void printResult(const char *key, int iters, double total_sec)
{
	double nsPerOp = (iters > 0) ? (total_sec * 1e9) / iters : 0.0;
	printf("%-12s %-12d %-14.6f %-14.2f\n",
		   key, iters, total_sec, nsPerOp);
}

/* --------------- Bench 1 : sequential malloc/free --------------- */

static double benchSeq(size_t size, int iters)
{
	double			t0 = nowSec();
	unsigned char	acc = 0;

	for (int i = 0; i < iters; i++) {
		void *p = malloc(size);
		if (!p) { fprintf(stderr, "OOM seq\n"); exit(1); }
		memset(p, 0xAA, size < 64 ? size : 64);
		compilerBarrier(p);
		acc ^= touchRead(p);
		free(p);
	}

	g_sink = (volatile void *)(uintptr_t)acc;   /* consume acc */
	return (nowSec() - t0);
}

/* --------------- Bench 2 : random pattern --------------- */

static double benchRandom(size_t maxSize, int iters)
{
	void			*live[MAX_LIVE] = {0};
	double			t0 = nowSec();
	unsigned char	acc = 0;

	for (int i = 0; i < iters; i++) {
		size_t idx = rngRange(MAX_LIVE);
		if (live[idx]) {
			acc ^= touchRead(live[idx]);
			free(live[idx]);
			live[idx] = NULL;
		} else {
			size_t sz = 1 + rngRange(maxSize);
			live[idx] = malloc(sz);
			if (live[idx]) {
				memset(live[idx], 0xBB, sz < 64 ? sz : 64);
				compilerBarrier(live[idx]);
			}
		}
	}

	for (int i = 0; i < MAX_LIVE; i++) {
		if (live[i]) {
			acc ^= touchRead(live[i]);
			free(live[i]);
		}
	}

	g_sink = (volatile void *)(uintptr_t)acc;
	return (nowSec() - t0);
}

/* --------------- Bench 3 : LIFO (stack-like) --------------- */

static double benchLifo(size_t size, int iters)
{
	void **stack = malloc(sizeof(void *) * MAX_LIVE);
	if (!stack) { fprintf(stderr, "OOM lifo stack\n"); exit(1); }

	double			t0 = nowSec();
	int				top = 0;
	unsigned char	acc = 0;

	for (int i = 0; i < iters; i++) {
		if (top == 0 || (top < MAX_LIVE && (rngNext() & 1))) {
			void *p = malloc(size);
			if (!p) { fprintf(stderr, "OOM lifo\n"); exit(1); }
			memset(p, 0xCC, size < 64 ? size : 64);
			compilerBarrier(p);
			stack[top++] = p;
		} else {
			void *p = stack[--top];
			acc ^= touchRead(p);
			free(p);
		}
	}

	while (top > 0) {
		void *p = stack[--top];
		acc ^= touchRead(p);
		free(p);
	}
	free(stack);

	g_sink = (volatile void *)(uintptr_t)acc;
	return (nowSec() - t0);
}

/* --------------- Bench 4 : FIFO (queue-like) --------------- */

static double benchFifo(size_t size, int iters)
{
	void **queue = malloc(sizeof(void *) * MAX_LIVE);
	if (!queue) { fprintf(stderr, "OOM fifo queue\n"); exit(1); }

	double			t0 = nowSec();
	int				head = 0, tail = 0, count = 0;
	unsigned char	acc = 0;

	for (int i = 0; i < iters; i++) {
		if (count < MAX_LIVE && (count == 0 || (rngNext() & 1))) {
			void *p = malloc(size);
			if (!p) { fprintf(stderr, "OOM fifo\n"); exit(1); }
			memset(p, 0xDD, size < 64 ? size : 64);
			compilerBarrier(p);
			queue[tail] = p;
			tail = (tail + 1) % MAX_LIVE;
			count++;
		} else if (count > 0) {
			void *p = queue[head];
			acc ^= touchRead(p);
			free(p);
			head = (head + 1) % MAX_LIVE;
			count--;
		}
	}

	while (count > 0) {
		void *p = queue[head];
		acc ^= touchRead(p);
		free(p);
		head = (head + 1) % MAX_LIVE;
		count--;
	}
	free(queue);

	g_sink = (volatile void *)(uintptr_t)acc;
	return (nowSec() - t0);
}

/* --------------- Bench 5 : realloc --------------- */

static double benchRealloc(int iters)
{
	double			t0 = nowSec();
	unsigned char	acc = 0;

	void *p = malloc(64);
	if (!p) { fprintf(stderr, "OOM realloc init\n"); return 0.0; }
	memset(p, 0xEE, 64);

	for (int i = 0; i < iters; i++) {
		size_t sz = 64 + rngRange(4096);
		void *np = realloc(p, sz);
		if (!np) {
			free(p);
			p = NULL;
			break;
		}
		p = np;
		memset(p, 0xEE, sz < 64 ? sz : 64);
		compilerBarrier(p);
		acc ^= touchRead(p);
	}

	if (p) {
		acc ^= touchRead(p);
		free(p);
	}

	g_sink = (volatile void *)(uintptr_t)acc;
	return (nowSec() - t0);
}

/* --------------- Bench 6 : calloc --------------- */

static double bench_calloc(size_t size, int iters)
{
	double			t0 = nowSec();
	unsigned char	acc = 0;

	for (int i = 0; i < iters; i++) {
		void *p = calloc(1, size);
		if (!p) { fprintf(stderr, "OOM calloc\n"); exit(1); }

		volatile unsigned char *vp = (volatile unsigned char *)p;
		for (size_t j = 0; j < size && j < 64; j++)
			acc ^= vp[j];

		compilerBarrier(p);
		free(p);
	}

	g_sink = (volatile void *)(uintptr_t)acc;
	return (nowSec() - t0);
}

/* --------------- Bench 7 : multithread --------------- */

typedef struct {
	int				iters;
	size_t			maxSize;
	double			elapsed;	/* temps du thread */
	unsigned char	acc;		/* anti-DCE */
} t_threadArg;

static void *threadWorker(void *arg)
{
	t_threadArg		*a = arg;
	void			*live[256] = {0};
	unsigned char	acc = 0;
	double			t0 = nowSec();

	for (int i = 0; i < a->iters; i++) {
		size_t idx = rngRange(256);
		if (live[idx]) {
			acc ^= touchRead(live[idx]);
			free(live[idx]);
			live[idx] = NULL;
		} else {
			size_t sz = 1 + rngRange(a->maxSize);
			live[idx] = malloc(sz);
			if (live[idx]) {
				memset(live[idx], 0x77, sz < 32 ? sz : 32);
				compilerBarrier(live[idx]);
			}
		}
	}

	for (int i = 0; i < 256; i++) {
		if (live[i]) {
			acc ^= touchRead(live[i]);
			free(live[i]);
		}
	}

	a->elapsed = nowSec() - t0;
	a->acc = acc;
	return (NULL);
}

static double benchThreads(int nthreads, int iters, size_t maxSize)
{
	pthread_t	th[NUM_THREADS];
	t_threadArg	args[NUM_THREADS];

	for (int i = 0; i < nthreads; i++) {
		args[i].iters = iters;
		args[i].maxSize = maxSize;
		args[i].elapsed = 0.0;
		args[i].acc = 0;
		pthread_create(&th[i], NULL, threadWorker, &args[i]);
	}

	double maxElapsed = 0.0;
	unsigned char acc = 0;
	for (int i = 0; i < nthreads; i++) {
		pthread_join(th[i], NULL);
		if (args[i].elapsed > maxElapsed)
			maxElapsed = args[i].elapsed;
		acc ^= args[i].acc;
	}

	g_sink = (volatile void *)(uintptr_t)acc;
	return (maxElapsed);
}

/* --------------- Bench 8 : fragmentation --------------- */
/*
 * Measure: allocate N small blocks, free every other one, then allocate
 * N/2 larger blocks into the holes. The measured time is for phase 3
 * (hole reuse). A fragmented allocator will take much longer because it
 * will need to create new regions.
 */
static double benchFragmentation(int iters)
{
	enum			{ N = 4096 };
	void			*ptrs[N] = {0};
	unsigned char	acc = 0;
	double			t0;

	for (int r = 0; r < iters; r++) {
		/* Phase 1 : N small blocks */
		for (int i = 0; i < N; i++) {
			ptrs[i] = malloc(64);
			if (!ptrs[i]) { fprintf(stderr, "OOM frag phase1\n"); exit(1); }
			memset(ptrs[i], 0x11, 64);
			compilerBarrier(ptrs[i]);
		}

		/* Phase 2 : free pairs of blocks to create holes */
		for (int i = 0; i < N; i += 2) {
			acc ^= touchRead(ptrs[i]);
			free(ptrs[i]);
			ptrs[i] = NULL;
		}

		/* Phase 3 (timed) : allocate larger blocks into the holes */
		t0 = nowSec();
		for (int i = 0; i < N; i += 2) {
			ptrs[i] = malloc(256);
			if (!ptrs[i]) { fprintf(stderr, "OOM frag phase3\n"); exit(1); }
			memset(ptrs[i], 0x22, 256);
			compilerBarrier(ptrs[i]);
		}
		double elapsed = nowSec() - t0;

		/* Cleanup */
		for (int i = 0; i < N; i++) {
			if (ptrs[i]) {
				acc ^= touchRead(ptrs[i]);
				free(ptrs[i]);
				ptrs[i] = NULL;
			}
		}

		g_sink = (volatile void *)(uintptr_t)acc;
		return (elapsed);	/* on ne fait qu'une itération */
	}

	g_sink = (volatile void *)(uintptr_t)acc;
	return (0.0);
}

/* --------------- Bench 9 : mixed workload --------------- */

static double benchMixed(int iters)
{
	void			*live[512] = {0};
	double			t0 = nowSec();
	unsigned char	acc = 0;

	for (int i = 0; i < iters; i++) {
		size_t idx = rngRange(512);
		int op = (int)(rngNext() % 4);

		if (live[idx] && op < 2) {
			/* 50% : free */
			acc ^= touchRead(live[idx]);
			free(live[idx]);
			live[idx] = NULL;
		} else if (live[idx] && op == 2) {
			/* 25% : realloc */
			size_t sz = 1 + rngRange(2048);
			void *np = realloc(live[idx], sz);
			if (!np) {
				free(live[idx]);
				live[idx] = NULL;
			} else {
				live[idx] = np;
				memset(np, 0x33, sz < 32 ? sz : 32);
				compilerBarrier(np);
			}
		} else {
			/* malloc (50%) or calloc (25%) */
			size_t sz = 1 + rngRange(2048);
			void *p = (op == 3) ? calloc(1, sz) : malloc(sz);
			if (!p) { fprintf(stderr, "OOM mixed\n"); exit(1); }
			if (op != 3)
				memset(p, 0x44, sz < 32 ? sz : 32);
			compilerBarrier(p);
			live[idx] = p;
		}
	}

	for (int i = 0; i < 512; i++) {
		if (live[i]) {
			acc ^= touchRead(live[i]);
			free(live[i]);
		}
	}

	g_sink = (volatile void *)(uintptr_t)acc;
	return (nowSec() - t0);
}

/* --------------- Bench 10 : large allocations --------------- */

static double benchLarge(int iters)
{
	static const size_t	sizes[] = { 128 * 1024, 256 * 1024,
										512 * 1024, 1 * 1024 * 1024,
										4 * 1024 * 1024 };
	const int			nsizes = sizeof(sizes) / sizeof(sizes[0]);

	double				t0 = nowSec();
	unsigned char		acc = 0;

	for (int i = 0; i < iters; i++) {
		size_t sz = sizes[i % nsizes];
		void *p = malloc(sz);
		if (!p) { fprintf(stderr, "OOM large\n"); exit(1); }
		acc ^= touchRead(p);
		acc ^= touchRead((char *)p + sz - 1);
		compilerBarrier(p);
		free(p);
	}

	g_sink = (volatile void *)(uintptr_t)acc;
	return (nowSec() - t0);
}



int main(int argc, char **argv)
{
	int quick = (argc > 1 && strcmp(argv[1], "--quick") == 0);
	int iters = quick ? BENCH_ITERS / 10 : BENCH_ITERS;
	char key[16];

	printf("# hmalloc benchmark\n");
	printf("# iters=%d warmup=%d\n", iters, WARMUP_ITERS);
#ifdef USE_GLIBC
	printf("# allocator: glibc\n");
#else
	printf("# allocator: hmalloc\n");
#endif

	/* Warmup : pre-allocate some memory to avoid measuring cold-start effects */
	for (int i = 0; i < WARMUP_ITERS; i++) {
		void *p = malloc(64);
		if (p) { compilerBarrier(p); free(p); }
	}
	for (int i = 0; i < WARMUP_ITERS; i++) {
		void *p = malloc(4096);
		if (p) { compilerBarrier(p); free(p); }
	}

	printHeader("malloc/free sequential");
	for (size_t s = 0; s < NUM_SIZES; s++) {
		size_t sz = g_sizes[s];
		int it = iters / 4;
		double t = benchSeq(sz, it);
		snprintf(key, sizeof(key), "%zu", sz);
		printResult(key, it, t);
	}

	printHeader("random pattern");
	double t = benchRandom(4096, iters);
	snprintf(key, sizeof(key), "%d", 4096);
	printResult(key, iters, t);

	printHeader("LIFO");
	t = benchLifo(128, iters);
	snprintf(key, sizeof(key), "%d", 128);
	printResult(key, iters, t);

	printHeader("FIFO");
	t = benchFifo(128, iters);
	snprintf(key, sizeof(key), "%d", 128);
	printResult(key, iters, t);

	printHeader("realloc");
	t = benchRealloc(iters / 4);
	snprintf(key, sizeof(key), "%s", "64-4K");
	printResult(key, iters / 4, t);

	printHeader("calloc");
	t = bench_calloc(128, iters);
	snprintf(key, sizeof(key), "%d", 128);
	printResult(key, iters, t);

	printHeader("multithread");
	t = benchThreads(NUM_THREADS, THREAD_ITERS, 512);
	snprintf(key, sizeof(key), "%d", NUM_THREADS);
	printResult(key, THREAD_ITERS, t);

	printHeader("fragmentation");
	t = benchFragmentation(1);
	printResult("holes", 2048, t);

	printHeader("mixed workload");
	t = benchMixed(iters / 4);
	printResult("mixed", iters / 4, t);

	printHeader("large (mmap)");
	t = benchLarge(iters / 100);
	printResult("large", iters / 100, t);

	printf("\n# done\n");
	return (0);
}
