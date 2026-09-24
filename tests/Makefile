# test/Makefile - build and run the hajlib test programs.
#
# This Makefile behaves like a user Makefile: it includes
# config.mk from hajlib, uses the HAJ_* variables, and does not
# know anything about the internal organization of hajlib.
#
# Targets:
#   all       build all test programs (default)
#   run       build and run all test programs
#   clean     remove build artifacts
#   fclean    same as clean
#   re        fclean + all
#   help      this message
#
# The library is built automatically if it does not exist. To
# disable this, pass HAJ_BUILD_LIB=0 on the command line.

HAJ_ROOT	:= ..

# Include the public configuration file. It defines:
#   CC, HAJ_CPPFLAGS, HAJ_CFLAGS, HAJ_LDFLAGS, HAJ_LIBS, HAJ_LIB
include $(HAJ_ROOT)/mk/config.mk

# Paths
TEST_DIR	:= .
BUILD_DIR	:= build

# Sources
include sources.mk

# Compiler flags
# We use the public flags from config.mk. If the user wants to
# add more flags, they can append to CFLAGS on the command line.
CFLAGS		:= $(HAJ_CFLAGS)
CFLAGS		+= -I$(TEST_DIR)

CPPFLAGS	:= $(HAJ_CPPFLAGS)

# Linker flags
LDFLAGS		:= $(HAJ_LDFLAGS)
LDLIBS		:= $(HAJ_LIBS)

# Binaries
TEST_BINS	:= $(patsubst %.c,$(BUILD_DIR)/%,$(TEST_SRCS))



# Phony targets
.PHONY: all run clean fclean re help

# Default: build all test binaries
all: $(TEST_BINS)

# Build the library if it does not exist
$(HAJ_LIB):
	$(MAKE) -C $(HAJ_ROOT) $(notdir $(HAJ_LIB))

# Rule: build a test binary
$(BUILD_DIR)/%: %.c $(HAJ_LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDLIBS) $(LDFLAGS) -o $@

# Run all test binaries
run: all
	@echo ""
	@echo "=== Running tests ==="
	@for t in $(TEST_BINS); do \
		echo ""; \
		echo "--- $$t ---"; \
		$$t || exit 1; \
	done
	@echo ""
	@echo "All tests passed."

# Clean
clean:
	@rm -rf $(BUILD_DIR)

fclean: clean

re: fclean all

# Help
help:
	@echo "Test targets:"
	@echo "  make          build all test programs"
	@echo "  make run      build and run all test programs"
	@echo "  make clean    remove build artifacts"
	@echo "  make fclean   same as clean"
	@echo "  make re       fclean + all"
	@echo "  make help     this message"
	@echo ""
	@echo "Variables:"
	@echo "  HAJ_ROOT      root of the hajlib source tree (default: ..)"
	@echo "  HAJ_BUILD_LIB if 1 (default), build libhajc.a if missing"
	@echo "                if 0, the library must already exist"
