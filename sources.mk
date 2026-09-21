# sources.mk - list of source files for hajlib.
#
# Each section corresponds to a public header. The section names
# are used by the Makefile to build per-section archives and to
# generate object file paths.
#
# Rules:
#   - Each section lists .c and .S files relative to its directory.
#   - No path in the variable itself; the Makefile prefixes with
#     the section directory.
#   - Use tab indentation, one file per line, with trailing backslash.
#
# To add a new file: add it to the right section.
# To add a new section: add a new SECTION_DIRS entry, a *_SRCS
# variable, and register the section in SECTIONS (Makefile).

# ---------------------------------------------------------------------------
# Section directories
# ---------------------------------------------------------------------------
CTYPE_DIR	:= src/ctype
STRING_DIR	:= src/string
STDLIB_DIR	:= src/stdlib
STDIO_DIR	:= src/stdio
MATH_DIR	:= src/math
TIME_DIR	:= src/time
SIGNAL_DIR	:= src/signal
UNISTD_DIR	:= src/unistd
FCNTL_DIR	:= src/fcntl
STAT_DIR	:= src/stat
MMAN_DIR	:= src/mman
GETOPT_DIR	:= src/getopt
ERRNO_DIR	:= src/errno


# ---------------------------------------------------------------------------
# ctype
# ---------------------------------------------------------------------------
CTYPE_SRCS := 

# ---------------------------------------------------------------------------
# string
# ---------------------------------------------------------------------------
STRING_SRCS := 

# ---------------------------------------------------------------------------
# stdlib
# ---------------------------------------------------------------------------
STDLIB_SRCS := 

# ---------------------------------------------------------------------------
# stdio
# ---------------------------------------------------------------------------
STDIO_SRCS := 

# ---------------------------------------------------------------------------
# math
# ---------------------------------------------------------------------------
MATH_SRCS := 

# ---------------------------------------------------------------------------
# time
# ---------------------------------------------------------------------------
TIME_SRCS := 

# ---------------------------------------------------------------------------
# signal
# ---------------------------------------------------------------------------
SIGNAL_SRCS := 

# ---------------------------------------------------------------------------
# unistd
# ---------------------------------------------------------------------------
UNISTD_SRCS := 

# ---------------------------------------------------------------------------
# fcntl
# ---------------------------------------------------------------------------
FCNTL_SRCS := 

# ---------------------------------------------------------------------------
# stat
# ---------------------------------------------------------------------------
STAT_SRCS := 

# ---------------------------------------------------------------------------
# mman
# ---------------------------------------------------------------------------
MMAN_SRCS := 

# ---------------------------------------------------------------------------
# getopt
# ---------------------------------------------------------------------------
GETOPT_SRCS := 

# ---------------------------------------------------------------------------
# errno
# ---------------------------------------------------------------------------
ERRNO_SRCS := \
	$(ERRNO_DIR)/errno.c \
	$(ERRNO_DIR)/strerror.c


# ---------------------------------------------------------------------------
# Prefix each section with its directory.
# ---------------------------------------------------------------------------
CTYPE_SRCS	:= $(addprefix $(CTYPE_DIR)/,$(CTYPE_SRCS))
STRING_SRCS	:= $(addprefix $(STRING_DIR)/,$(STRING_SRCS))
STDLIB_SRCS	:= $(addprefix $(STDLIB_DIR)/,$(STDLIB_SRCS))
STDIO_SRCS	:= $(addprefix $(STDIO_DIR)/,$(STDIO_SRCS))
MATH_SRCS	:= $(addprefix $(MATH_DIR)/,$(MATH_SRCS))
TIME_SRCS	:= $(addprefix $(TIME_DIR)/,$(TIME_SRCS))
SIGNAL_SRCS	:= $(addprefix $(SIGNAL_DIR)/,$(SIGNAL_SRCS))
UNISTD_SRCS	:= $(addprefix $(UNISTD_DIR)/,$(UNISTD_SRCS))
FCNTL_SRCS	:= $(addprefix $(FCNTL_DIR)/,$(FCNTL_SRCS))
STAT_SRCS	:= $(addprefix $(STAT_DIR)/,$(STAT_SRCS))
MMAN_SRCS	:= $(addprefix $(MMAN_DIR)/,$(MMAN_SRCS))
GETOPT_SRCS	:= $(addprefix $(GETOPT_DIR)/,$(GETOPT_SRCS))
ERRNO_SRCS	:= $(addprefix $(ERRNO_DIR)/,$(ERRNO_SRCS))
