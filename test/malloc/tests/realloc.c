/**
 * @brief Tests for realloc.
 * This test suite checks the functionality of the realloc function.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	/* 1. realloc(NULL, n) == malloc(n) */
	void *p = realloc(NULL, 128);
	if (!p) { fprintf(stderr, "realloc(NULL) failed\n"); return 1; }
	memset(p, 0xAA, 128);

	/* 2. realloc(p, 0) == free(p) */
	p = realloc(p, 0);
	/* p can be NULL or a valid pointer. */

	/* 3. realloc to a larger size and check that data is preserved */
	unsigned char *q = malloc(64);
	for (int i = 0; i < 64; i++) q[i] = i;
	q = realloc(q, 256);
	if (!q) { fprintf(stderr, "realloc grow failed\n"); return 1; }
	for (int i = 0; i < 64; i++)
		if (q[i] != (unsigned char)i) { fprintf(stderr, "realloc lost data!\n"); return 1; }

	/* 4. realloc to a smaller size and check that data is preserved */
	q = realloc(q, 16);
	if (!q) { fprintf(stderr, "realloc shrink failed\n"); return 1; }
	for (int i = 0; i < 16; i++)
		if (q[i] != (unsigned char)i) { fprintf(stderr, "realloc lost data (shrink)!\n"); return 1; }
	free(q);

	/* 5. Stress test: repeatedly realloc a block to different sizes */
	void *r = malloc(64);
	for (int i = 0; i < 10000; i++) {
		r = realloc(r, (i % 4096) + 1);
		if (!r) { fprintf(stderr, "realloc loop failed at %d\n", i); return 1; }
		memset(r, i & 0xFF, 1);
	}
	free(r);

	/* 6. Check that realloc can merge adjacent free blocks */
	void *a = malloc(64);
	void *b = malloc(64);
	free(b);
	a = realloc(a, 100);   /* Should be able to expand into b's space */
	if (!a) { fprintf(stderr, "realloc merge failed\n"); return 1; }
	memset(a, 0xBB, 100);
	free(a);

	printf("ALL REALLOC TESTS PASSED\n");
	return (0);
}
