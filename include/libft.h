/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:47:48 by ele-lean          #+#    #+#             */
/*   Updated: 2025/02/24 17:43:12 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//Part1
int				ft_atoi(const char *str);
void			*ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *src);
unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
size_t			ft_strlen(const char *string);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);

//Part2
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

//PART BONUS
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
//EXTRA
long			ft_atol(const char *str);
int				get_sign(const char **str);
int				ft_tablen(void **tab);
void			free_tab(void **tab);
void			free_list(t_list *list);
int				ft_getnline(char *file);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strpos(const char *str, char c);
char			*ft_addchar(char *str, char c);
char			*ft_strcut(char *str, char c);
t_list			*ft_lstget(t_list *list, int index);
void			**ft_realloctab(void **array, size_t old_size, size_t new_size);
void			ft_removenode(t_list **head,
					void *to_remove, void (*del)(void *));
int				ft_is_empty_string(char *str);
char			*ft_strjoin_free(char *s1, char *s2,
					int free_s1, int free_s2);
char			*ft_strstr(char *haystack, char *needle);
char			*ft_str_replace(char *str, char *to_replace, char *replacement);
void			ft_remove_duplicates(char *str);
char			*ft_strndup(const char *s, size_t n);
void			ft_lstinsert_after(t_list *current, t_list *new_node);
int				ft_atoi_base(char *str, char *base);
char			*ft_dtoa(double n, int precision);

//PRINTF
int				ft_printf(const char *str, ...);

//GET_NEXT_LINE
char			*get_next_line(int fd);

//MLX

#define FONT_SIZE 1
#define FONT_SPACING 5
#define FONT_SPACE 30

typedef struct s_mlx_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_mlx_img;

typedef struct s_mlx_letter
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	align;
}	t_mlx_letter;
typedef struct s_mlx_font
{
	t_mlx_img		*font;
	t_mlx_img		*screen;
	char			*letters_str;
	t_mlx_letter	*letters;
	int				letter_spacing;
	int				font_size;
	int				color;
	char			*path;
	int				space_width;
	void			*mlx;
}	t_mlx_font;

int				mlx_new_font(t_mlx_font *font);
int				ft_mlx_put_string(t_mlx_font *font, char *str, int x, int y);
void			clear_mlx_font(t_mlx_font *font);

int				mlx_destroy_image(void *mlx_ptr, void *img_ptr);