CC		= clang
CFLAGS	= -g -Wall -Werror -Wextra -Iinclude -O3 -march=native
NAME	= hajlib.a
OBJDIR	= objs

include sources.mk

SECTIONS = CHAR STRING MATH MEMORY LIST IO PRINTF UTIL

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
	ar rcs $@ $^

# Generic object compilation
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# =====================
# Section-specific builds
# =====================
char: $(CHAR_OBJS)
	ar rcs $(OBJDIR)/char.a $^

string: $(STRING_OBJS)
	ar rcs $(OBJDIR)/string.a $^

math: $(MATH_OBJS)
	ar rcs $(OBJDIR)/math.a $^

memory: $(MEMORY_OBJS)
	ar rcs $(OBJDIR)/memory.a $^

list: $(LIST_OBJS)
	ar rcs $(OBJDIR)/list.a $^

io: $(IO_OBJS)
	ar rcs $(OBJDIR)/io.a $^

printf: $(PRINTF_OBJS)
	ar rcs $(OBJDIR)/printf.a $^

util: $(UTIL_OBJS)
	ar rcs $(OBJDIR)/util.a $^

# =====================
# Clean
# =====================
clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(OBJDIR)/*.a

re: fclean all

.PHONY: all clean fclean re char string math memory list io printf util
