/**
 * @brief Stress test for malloc/free.
 * This test allocates and frees random-sized blocks in a loop, checking for
 * memory corruption. It is designed to stress the allocator and detect bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define N		100000
#define LIVE	8192

static uint64_t rng = 0xdeadbeefcafebabeULL;
static uint64_t next(void) {
	rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17;
	return (rng);
}

typedef struct { void *p; size_t sz; unsigned char tag; } slot_t;

int main(void)
{
	slot_t live[LIVE] = {{0}};
	size_t total_allocs = 0;

	for (int i = 0; i < N; i++) {
		size_t idx = next() % LIVE;
		if (live[idx].p) {
			/* Check that the block still contains the expected tag */
			unsigned char *q = live[idx].p;
			for (size_t j = 0; j < live[idx].sz; j++) {
				if (q[j] != live[idx].tag) {
					fprintf(stderr, "CORRUPTION at iter %d, slot %zu, byte %zu\n",
							i, idx, j);
					return (1);
				}
			}
			free(live[idx].p);
			live[idx].p = NULL;
		} else {
			size_t sz = 1 + next() % 8192;
			unsigned char tag = (unsigned char)(next() & 0xFF);
			void *p = malloc(sz);
			if (!p) { fprintf(stderr, "OOM at iter %d (sz=%zu)\n", i, sz); return 1; }
			memset(p, tag, sz);
			live[idx].p = p;
			live[idx].sz = sz;
			live[idx].tag = tag;
			total_allocs++;
		}
	}

	for (int i = 0; i < LIVE; i++) {
		if (live[i].p) {
			unsigned char *q = live[i].p;
			for (size_t j = 0; j < live[i].sz; j++)
				if (q[j] != live[i].tag) { fprintf(stderr, "final corruption\n"); return 1; }
			free(live[i].p);
		}
	}

	printf("STRESS TEST PASSED (%zu allocations)\n", total_allocs);
	return (0);
}
