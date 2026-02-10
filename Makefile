# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 14:24:19 by ele-lean          #+#    #+#              #
#    Updated: 2025/02/21 08:48:12 by ele-lean         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I$(INCLUDE_DIR) -fPIC -O3
NAME = libft.a

PART1_DIR = src/part1
PART2_DIR = src/part2
PART_BONUS_DIR = src/bonus
PART_EXTRA_DIR = src/extra
PART_PRINTF_DIR = ft_printf
PART_GET_NEXT_LINE_DIR = get_next_line
PART_MLX_DIR = mlx
INCLUDE_DIR = include

PART1_SRCS = ft_atoi.c ft_isalpha.c ft_memchr.c ft_memset.c ft_strlcpy.c \
			 ft_strrchr.c ft_bzero.c ft_isascii.c ft_memcmp.c ft_strchr.c \
			 ft_strlen.c ft_tolower.c ft_calloc.c ft_isdigit.c ft_memcpy.c \
			 ft_strdup.c ft_strncmp.c ft_toupper.c ft_isalnum.c ft_isprint.c \
			 ft_memmove.c ft_strlcat.c ft_strnstr.c

PART2_SRCS = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			 ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

PART_BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
				  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				  ft_lstmap.c

PART_EXTRA_SRCS = ft_atol.c ft_tablen.c free_tab.c free_list.c ft_getnline.c ft_strcmp.c \
				  ft_strpos.c ft_addchar.c ft_strcut.c ft_lstget.c \
				  ft_realloctab.c ft_removenode.c ft_is_empty_string.c ft_strjoin_free.c \
				  ft_strstr.c ft_str_replace.c ft_remove_duplicates.c ft_lstinsert_after.c \
				  ft_strndup.c ft_atoi_base.c ft_dtoa.c

PART_PRINTF_SRCS = ft_printf.c utils.c print_args.c print_argsbis.c manage_flags.c

PART_GET_NEXT_LINE_SRCS = get_next_line.c get_next_line_utils.c

PART_MLX_SRCS = ft_mlx_put_string.c parse_font.c

PART1_OBJS = $(addprefix $(PART1_DIR)/, $(PART1_SRCS:.c=.o))
PART2_OBJS = $(addprefix $(PART2_DIR)/, $(PART2_SRCS:.c=.o))
PART_BONUS_OBJS = $(addprefix $(PART_BONUS_DIR)/, $(PART_BONUS_SRCS:.c=.o))
PART_EXTRA_OBJS = $(addprefix $(PART_EXTRA_DIR)/, $(PART_EXTRA_SRCS:.c=.o))
PART_PRINTF_OBJS = $(addprefix $(PART_PRINTF_DIR)/, $(PART_PRINTF_SRCS:.c=.o))
PART_GET_NEXT_LINE_OBJS = $(addprefix $(PART_GET_NEXT_LINE_DIR)/, $(PART_GET_NEXT_LINE_SRCS:.c=.o))
PART_MLX_OBJ = $(addprefix $(PART_MLX_DIR)/, $(PART_MLX_SRCS:.c=.o))

OBJS = $(PART1_OBJS) $(PART2_OBJS) $(PART_BONUS_OBJS) $(PART_EXTRA_OBJS) $(PART_PRINTF_OBJS) $(PART_GET_NEXT_LINE_OBJS) $(PART_MLX_OBJ)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
