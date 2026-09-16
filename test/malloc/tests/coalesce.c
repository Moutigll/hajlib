/**
 * @brief Tests for memory coalescing.
 * This test suite checks the functionality of the memory allocator's coalescing behavior.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	/* 1. Allocate three blocks, free the first two, and check if they coalesce into a larger block. */
	void *a = malloc(1000);
	void *b = malloc(1000);
	void *c = malloc(1000);
	memset(a, 1, 1000);
	memset(b, 2, 1000);
	memset(c, 3, 1000);

	free(a);
	free(b);
	void *d = malloc(1900);
	if (!d) { fprintf(stderr, "FAIL: coalesce forward\n"); return 1; }
	free(c);
	free(d);

	/* 2. Allocate three blocks, free the last two, and check if they coalesce into a larger block. */
	a = malloc(1000);
	b = malloc(1000);
	c = malloc(1000);
	free(b);
	free(a);
	d = malloc(1900);
	if (!d) { fprintf(stderr, "FAIL: coalesce backward\n"); return 1; }
	free(c);
	free(d);

	/* 3. Allocate three blocks, free the first and last, and check if they coalesce into a larger block. */
	a = malloc(1000);
	b = malloc(1000);
	c = malloc(1000);
	free(a);
	free(c);
	free(b);
	d = malloc(2900);
	if (!d) { fprintf(stderr, "FAIL: triple coalesce\n"); return 1; }
	free(d);

	printf("ALL COALESCE TESTS PASSED\n");
	return (0);
}
