# ===============================================
# Benchmark + unit tests for hmalloc / libhaj
# ===============================================

CC			?= clang
CFLAGS		?= -O2 -g -Wall -Wextra -Wno-unused-parameter -pthread
CPPFLAGS	:= -I$(PROJECT_ROOT)/include
PROJECT_ROOT	:= ../..
HAJ_LIB		:= $(PROJECT_ROOT)/libhaj.a
HAJ_INC		:= $(PROJECT_ROOT)/include

include sources.mk

.PHONY: all clean bench test tests run-bench-glibc run-bench-hmalloc run-tests

all: bench test

# --- directories ------------------------------------------------------
$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/tests:
	@mkdir -p $@

# --- generic object compilation --------------------------------------
$(BUILD_DIR)/bench.o: $(BENCH_DIR)/$(BENCH_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -DUSE_GLIBC -c $< -o $@

$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.c $(HAJ_LIB) | $(BUILD_DIR) $(BUILD_DIR)/tests
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# --- benchmark binaries -----------------------------------------------
bench_glibc: $(BUILD_DIR)/bench_glibc
$(BUILD_DIR)/bench_glibc: $(BENCH_DIR)/bench.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -DUSE_GLIBC -o $@ $<

bench_hmalloc: $(BUILD_DIR)/bench_hmalloc
$(BUILD_DIR)/bench_hmalloc: $(BENCH_DIR)/bench.c $(HAJ_LIB) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -DUSE_HMALLOC -o $@ $< \
		-Wl,--whole-archive $(HAJ_LIB) -Wl,--no-whole-archive

bench: run-bench-glibc run-bench-hmalloc
	@echo ">>> Comparing benchmark outputs..."
	@python3 compare.py results_glibc.txt results_hmalloc.txt

run-bench-glibc: $(BUILD_DIR)/bench_glibc
	@echo ">>> Running glibc benchmark..."
	@./$(BUILD_DIR)/bench_glibc > results_glibc.txt 2>&1

run-bench-hmalloc: $(BUILD_DIR)/bench_hmalloc
	@echo ">>> Running hmalloc benchmark..."
	@./$(BUILD_DIR)/bench_hmalloc > results_hmalloc.txt 2>&1

# --- tests -----------------------------------------------------------
$(BUILD_DIR)/tests/%: $(TEST_DIR)/%.c $(HAJ_LIB) | $(BUILD_DIR) $(BUILD_DIR)/tests
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< \
		-Wl,--whole-archive $(HAJ_LIB) -Wl,--no-whole-archive

test: $(TEST_BINS)

run-tests: test
	@for t in $(TEST_BINS); do \
		echo "=== $$t ==="; \
		$$t || exit $$?; \
	done

plot: bench
	@python3 bench_plot.py results_glibc.txt results_hmalloc.txt

clean:
	@rm -rf $(BUILD_DIR) results_*.txt *.png
