# ========================================
# Sources for malloc tests and benchmarks
# ========================================

BUILD_DIR := build

BENCH_DIR := .
BENCH_SRC := bench.c
BENCH_TARGETS := bench_glibc bench_hmalloc

TEST_DIR := tests
TEST_SRC := alignment.c \
		basic.c \
		calloc.c \
		coalesce.c \
		realloc.c \
		stress.c

TEST_BINS := $(patsubst %.c,$(BUILD_DIR)/tests/%,$(TEST_SRC))
TEST_OBJS := $(patsubst %.c,$(BUILD_DIR)/tests/%.o,$(TEST_SRC))
BENCH_OBJS := $(BUILD_DIR)/bench.o

# Optional convenience variables used by the Makefile
BENCH_BIN_GLIBC := bench_glibc
BENCH_BIN_HMALLOC := bench_hmalloc
TEST_BIN_DIR := $(BUILD_DIR)/tests
