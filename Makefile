# --- Configuration ---
CFLAGS	= -Wall -Werror -Wextra -Iinclude -O3 -march=native -DUSE_PARITY_TABLE --pedantic
CFLAGS	+= $(addprefix -D,$(DEFINES))
NAME	= libhaj.a
OBJDIR	= objs

ARCH := $(shell uname -m 2>/dev/null || echo x86_64)

include sources.mk

# --- Cross-compilation settings ---
include cross.mk

ifeq ($(CROSS_COMPILING),1)
	CFLAGS := $(filter-out -march=native,$(CFLAGS))
	CFLAGS := $(filter-out -Werror,$(CFLAGS))
endif

SECTIONS = CHAR STRING MALLOC MATH MEMORY LIST IO GNL PRINTF UTIL

# Add popcnt optimization for GF(2^n) operations if supported
ifeq ($(ARCH),x86_64)
	ifeq ($(CROSS_COMPILING),0)
		CFLAGS += -mpopcnt
	endif
endif

# Map section sources to object files
define make_objects
$1_OBJS := $(patsubst src/%,$(OBJDIR)/%,$($1_SRCS:.c=.o))
endef

$(foreach sec,$(SECTIONS),$(eval $(call make_objects,$(sec))))
ALL_OBJS := $(foreach sec,$(SECTIONS),$($(sec)_OBJS))

# Create all needed directories before compilation
DIRS := $(sort $(dir $(ALL_OBJS)))

all: $(NAME)

# Full library
$(NAME): $(ALL_OBJS)
	$(AR) rcs $@ $^

# Generic object compilation
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# =====================
# Section-specific builds
# =====================
char: $(CHAR_OBJS)
	$(AR) rcs $(OBJDIR)/char.a $^

string: $(STRING_OBJS)
	$(AR) rcs $(OBJDIR)/string.a $^

malloc: $(MALLOC_OBJS)
	$(AR) rcs $(OBJDIR)/malloc.a $^

math: $(MATH_OBJS)
	$(AR) rcs $(OBJDIR)/math.a $^

memory: $(MEMORY_OBJS)
	$(AR) rcs $(OBJDIR)/memory.a $^

list: $(LIST_OBJS)
	$(AR) rcs $(OBJDIR)/list.a $^

io: $(IO_OBJS)
	$(AR) rcs $(OBJDIR)/io.a $^

gnl: $(GNL_OBJS)
	ar rcs $(OBJDIR)/gnl.a $^

printf: $(PRINTF_OBJS)
	$(AR) rcs $(OBJDIR)/printf.a $^

util: $(UTIL_OBJS)
	$(AR) rcs $(OBJDIR)/util.a $^

# =====================
# Clean
# =====================
clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(OBJDIR)/*.a

re: fclean all

.PHONY: all clean fclean re char string malloc math memory list io gnl printf util
