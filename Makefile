# ----------------------------------------------------------------------------
# hajlib - Makefile
# ----------------------------------------------------------------------------
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
# ----------------------------------------------------------------------------


# Version (extracted from include/haj/version.h)
include version.mk

# Base configuration
NAME		:= libhaj.a
OBJDIR		:= objs

CPPFLAGS	:= -Iinclude
CFLAGS		:= -Wall -Wextra -Werror -O2 -std=c11 -pedantic

# Cross-compilation settings (must come before source selection)
include cross.mk

# Sources
include sources.mk
include syscall.mk

# Build rules
include build.mk

# Collect all source files and object files
ALL_SRCS := \
	$(CTYPE_SRCS) \
	$(STRING_SRCS) \
	$(STDLIB_SRCS) \
	$(STDIO_SRCS) \
	$(MATH_SRCS) \
	$(GALLOIS_SRCS) \
	$(TIME_SRCS) \
	$(SIGNAL_SRCS) \
	$(UNISTD_SRCS) \
	$(FCNTL_SRCS) \
	$(STAT_SRCS) \
	$(MMAN_SRCS) \
	$(GETOPT_SRCS) \
	$(ERRNO_SRCS) \
	$(LIST_SRCS) \
	$(GNL_SRCS) \
	$(SYSCALL_SRCS)

ALL_OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(patsubst %.S,$(OBJDIR)/%.o,$(ALL_SRCS)))



# Default target
all: $(NAME)

$(NAME): $(ALL_OBJS)
	$(AR) rcs $@ $^

# Info targets
.PHONY: version info help clean fclean re

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
	@echo "See cross.mk for details."

# Clean
clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
