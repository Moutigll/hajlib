#ifndef HAJLIB_IO_H
#define HAJLIB_IO_H

/**
 * @brief Get the number of lines in a specified file.
 * @param file - The file path to read.
 * @return The number of lines in the specified file, or -1 if there is an error.
 */
int		ft_getnline(char *file);

/**
 * @brief Write a character to the specified file descriptor.
 * @param c - The character to write.
 * @param fd - The file descriptor to write to.
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Write a string followed by a newline to the specified file descriptor.
 * @param s - The string to write.
 * @param fd - The file descriptor to write to.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Write an integer to the specified file descriptor.
 * @param n - The integer to write.
 * @param fd - The file descriptor to write to.
 */
void	ft_putnbr_fd(int n, int fd);

/**
 * @brief Write a string to the specified file descriptor.
 * @param s - The string to write.
 * @param fd - The file descriptor to write to.
 */
int		ft_putstr_fd(char *s, int fd);

#endif /* HAJLIB_IO_H */
