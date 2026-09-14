/**
 * @brief Basic tests for malloc and free.
 * This test suite checks the basic functionality of the memory allocator.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CHECK(cond, msg) do { \
	if (!(cond)) { fprintf(stderr, "FAIL: %s (%s:%d)\n", msg, __FILE__, __LINE__); exit(1); } \
} while (0)

int main(void)
{
	/* 1. malloc(0) : Undefined behavior, but should not crash. */
	void *p0 = malloc(0);
	printf("malloc(0) = %p\n", p0);
	free(p0);

	/* 2. malloc/free with various sizes and check read/write */
	size_t sizes[] = {1, 7, 8, 15, 16, 17, 31, 32, 33, 63, 64, 65,
					  127, 128, 129, 255, 256, 257, 1023, 1024,
					  4096, 8192, 65536, 1 << 20};
	for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
		size_t sz = sizes[i];
		unsigned char *p = malloc(sz);
		CHECK(p != NULL, "malloc returned non-NULL");
		memset(p, 0xAB, sz);
		for (size_t j = 0; j < sz; j++)
			assert(p[j] == 0xAB);
		free(p);
	}
	printf("ok: malloc/free with various sizes (write/read)\n");

	/* 3. free(NULL) should be safe and do nothing */
	free(NULL);
	printf("ok: free(NULL)\n");

	/* 4. Stress test: allocate many blocks and free them */
	enum { N = 10000 };
	void **ptrs = malloc(N * sizeof(void *));
	for (int i = 0; i < N; i++) {
		ptrs[i] = malloc((i % 512) + 1);
		CHECK(ptrs[i] != NULL, "bulk malloc");
		memset(ptrs[i], i & 0xFF, (i % 512) + 1);
	}
	for (int i = 0; i < N; i++)
		free(ptrs[i]);
	free(ptrs);
	printf("ok: 10000 simultaneous allocations\n");

	printf("\nALL BASIC TESTS PASSED\n");
	return (0);
}
