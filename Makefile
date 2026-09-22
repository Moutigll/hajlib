# hajlib - Makefile
#
# A POSIX-like C library, no libc dependency, multi-OS multi-arch.
#
# Targets:
#   all       build libhaj.a (default)
#   clean     remove object files
#   fclean    remove object files and the library
#   re        fclean + all
#   version   print the current version
#   info      print build configuration
#   help      this message
#
# Cross-compilation:
#   make WIN64=1         compile for 64-bit Windows (mingw)
#   make WIN32=1         compile for 32-bit Windows (mingw)
#   make NATIVE=1        force native compilation
#

# Configuration (toolchain, flags, public paths)
HAJ_ROOT := $(CURDIR)
include mk/config.mk
# Cross-compilation (must come before source selection)
include mk/cross.mk
# Version (extracted from include/haj/version.h)
include mk/version.mk

# Sources (portable + OS/arch-specific)
include mk/sources.mk
include mk/targets.mk

# Build rules
include mk/build.mk

# Library name-
NAME		:= libhaj.a
OBJDIR		:= objs

# Collect all source files
# The order matters: low-level modules first, high-level after.
# The linker scans the archive from left to right and picks the
# objects that resolve unresolved symbols.
ALL_SRCS := \
	$(CRT_SRCS) \
	$(CRT_START_SRCS) \
	$(SYSCALL_SRCS) \
	$(SETJMP_SRCS) \
	$(SIGSETJMP_SRCS) \
	$(RUNTIME_SRCS) \
	$(STACK_CHK_SRCS) \
	$(ASSERT_SRCS) \
	$(ERRNO_SRCS) \
	$(STRING_SRCS) \
	$(FCNTL_SRCS) \
	$(CTYPE_SRCS) \
	$(STDLIB_SRCS) \
	$(STDIO_SRCS) \
	$(MATH_SRCS) \
	$(TIME_SRCS) \
	$(SIGNAL_SRCS) \
	$(UNISTD_SRCS) \
	$(STAT_SRCS) \
	$(MMAN_SRCS) \
	$(GETOPT_SRCS)

ALL_OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(patsubst %.S,$(OBJDIR)/%.o,$(ALL_SRCS)))

# Info targets
.PHONY: version info help clean fclean re

# Default target
all: $(NAME)

$(NAME): $(ALL_OBJS)
	$(AR) rcs $@ $^

version:
	@echo "$(HAJ_VERSION)"

info:
	@echo "hajlib version  : $(HAJ_VERSION)"
	@echo "Target OS       : $(TARGET_OS)"
	@echo "Target arch     : $(TARGET_ARCH)"
	@echo "Compiler        : $(CC)"
	@echo "Archiver        : $(AR)"
	@echo "Cross-compiling : $(CROSS_COMPILING)"
	@echo "Sources         : $(words $(ALL_SRCS)) files"
	@echo "Objects         : $(words $(ALL_OBJS)) files"

help:
	@echo "hajlib targets:"
	@echo "  make          build libhaj.a"
	@echo "  make clean    remove object files"
	@echo "  make fclean   remove object files and the library"
	@echo "  make re       fclean + all"
	@echo "  make version  print the current version"
	@echo "  make info     print build configuration"
	@echo "  make help     this message"
	@echo ""
	@echo "Cross-compilation:"
	@echo "  make WIN64=1  compile for 64-bit Windows (mingw)"
	@echo "  make WIN32=1  compile for 32-bit Windows (mingw)"
	@echo "  make NATIVE=1 force native compilation"
	@echo ""
	@echo "See mk/cross.mk for details."

# Clean
clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
