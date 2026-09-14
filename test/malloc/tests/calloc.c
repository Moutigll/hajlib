/**
 * @brief Tests for calloc.
 * This test suite checks the functionality of the calloc function.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	/* 1. calloc should return zeroed memory */
	int *p = calloc(10, sizeof(int));
	if (!p) { fprintf(stderr, "calloc failed\n"); return 1; }
	for (int i = 0; i < 10; i++)
		if (p[i] != 0) { fprintf(stderr, "calloc not zeroed!\n"); return 1; }
	free(p);

	/* 2. calloc with various sizes */
	for (size_t sz = 1; sz <= 65536; sz *= 2) {
		unsigned char *q = calloc(sz, 1);
		if (!q) { fprintf(stderr, "calloc(%zu) failed\n", sz); return 1; }
		for (size_t i = 0; i < sz; i++)
			if (q[i] != 0) { fprintf(stderr, "calloc not zeroed at %zu\n", i); return 1; }
		free(q);
	}

	/* 3. Mixed malloc/calloc/free to check for any issues with the allocator */
	for (int i = 0; i < 1000; i++) {
		void *a = malloc(64);
		void *b = calloc(1, 64);
		void *c = malloc(128);
		memset(a, 1, 64);
		memset(c, 2, 128);
		free(a);
		free(b);
		free(c);
	}

	/* 4. calloc(0, x) and calloc(x, 0) */
	void *z1 = calloc(0, 10);
	void *z2 = calloc(10, 0);
	free(z1);
	free(z2);

	printf("ALL CALLOC TESTS PASSED\n");
	return (0);
}
