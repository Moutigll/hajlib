# ======================
# Sources for libft
# ======================

# Directories
CHAR_DIR	= src/char
STRING_DIR	= src/string
MATH_DIR	= src/math
MEMORY_DIR	= src/memory
LIST_DIR	= src/list
IO_DIR		= src/io
PRINTF_DIR	= $(IO_DIR)/ft_printf
GNL_DIR		= $(IO_DIR)/gnl
UTIL_DIR	= src/util

# Char functions
CHAR_SRCS	=	ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_tolower.c \
				ft_toupper.c

# String functions
STRING_SRCS	=	ft_putchar_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strcut.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strjoin_free.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strndup.c \
				ft_strnstr.c \
				ft_strpos.c \
				ft_strrchr.c \
				ft_str_replace.c \
				ft_strstr.c \
				ft_strtrim.c \
				ft_substr.c

# Math functions
MATH_SRCS	=	ft_atoi.c \
				ft_atol.c \
				ft_atoi_base.c \
				ft_dtoa.c \
				ft_itoa.c

# Memory functions
MEMORY_SRCS	=	ft_bzero.c \
				ft_calloc.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c

# List functions
LIST_SRCS	=	free_list.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstget.c \
				ft_lstinsert_after.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c

# IO functions
IO_SRCS		=	ft_getnline.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c

GNL_SRCS	=	ft_get_next_line.c \
				ft_get_next_line_utils.c

PRINTF_SRCS	=	ft_printf.c \
				utils.c \
				manage_flags.c \
				print_args.c \
				print_argsbis.c

# Util functions
UTIL_SRCS	=	free_tab.c \
				ft_addchar.c \
				ft_is_empty_string.c \
				ft_realloctab.c \
				ft_remove_duplicates.c \
				ft_removenode.c \
				ft_tablen.c

# Convert to full paths
CHAR_SRCS	:= $(addprefix $(CHAR_DIR)/,$(CHAR_SRCS))
STRING_SRCS	:= $(addprefix $(STRING_DIR)/,$(STRING_SRCS))
MATH_SRCS	:= $(addprefix $(MATH_DIR)/,$(MATH_SRCS))
MEMORY_SRCS	:= $(addprefix $(MEMORY_DIR)/,$(MEMORY_SRCS))
LIST_SRCS	:= $(addprefix $(LIST_DIR)/,$(LIST_SRCS))
IO_SRCS		:= $(addprefix $(IO_DIR)/,$(IO_SRCS))
PRINTF_SRCS	:= $(addprefix $(PRINTF_DIR)/,$(PRINTF_SRCS))
GNL_SRCS	:= $(addprefix $(GNL_DIR)/,$(GNL_SRCS))
UTIL_SRCS	:= $(addprefix $(UTIL_DIR)/,$(UTIL_SRCS))