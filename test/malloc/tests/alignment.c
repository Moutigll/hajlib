/**
 * @brief Test if malloc returns pointers aligned to 16 bytes.
 * This is important for performance and correctness on many platforms.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define CHECK_ALIGN(p, n) do { \
	if (((uintptr_t)(p)) % (n) != 0) { \
		fprintf(stderr, "FAIL: %p not aligned to %d\n", (void*)(p), (n)); \
		return 1; \
	} \
} while (0)

int main(void)
{
	/* All mallocs should return pointers aligned to 16 bytes */
	for (size_t sz = 1; sz <= 4096; sz++) {
		void *p = malloc(sz);
		if (!p) { fprintf(stderr, "malloc(%zu) failed\n", sz); return 1; }
		CHECK_ALIGN(p, 16);
		free(p);
	}

	void *ptrs[1000];
	for (int i = 0; i < 1000; i++) {
		ptrs[i] = malloc((i * 7) % 1024 + 1);
		CHECK_ALIGN(ptrs[i], 16);
	}
	for (int i = 0; i < 1000; i++) free(ptrs[i]);

	printf("ALL ALIGNMENT TESTS PASSED\n");
	return (0);
}
