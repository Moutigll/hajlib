#ifndef HAJLIB_UTILS_H
#define HAJLIB_UTILS_H

#include <stddef.h>

/**
 * @brief Frees a null-terminated array of pointers and the pointers themselves.
 * @param tab - A null-terminated array of pointers to be freed.
 */
void	free_tab(void **tab);

/**
 * @brief Adds a character to the end of a string, reallocating memory as needed.
 * @param str - The original string to which the character will be added. Can be NULL.
 * @param c - The character to add to the string.
 * @return A new string with the character added. The caller is responsible for freeing this memory.
 */
char	*ft_addchar(char *str, char c);

/**
 * @brief Checks if a string is empty (i.e., has a length of zero).
 * @param str - The string to check.
 * @return 1 if the string is empty, 0 otherwise.
 */
int		ft_is_empty_string(char *str);

/**
 * @brief Reallocates a null-terminated array of pointers to a new size.
 * @param array - The original array of pointers to be reallocated. Can be NULL.
 * @param old_size - The current size of the array (number of elements).
 * @param new_size - The desired size of the array (number of elements).
 * @return A new array of pointers with the specified new size. The caller is responsible for freeing this memory.
 */
void	**ft_realloctab(void **array, size_t old_size, size_t new_size);

/**
 * @brief Removes duplicate characters from a string in place.
 * @param str - The string from which duplicate characters will be removed. The string is modified directly.
 */
void	ft_remove_duplicates(char *str);

/**
 * @brief Counts the number of elements in a null-terminated array of pointers.
 * @param tab - A null-terminated array of pointers.
 * @return The number of elements in the array (excluding the null terminator).
 */
int		ft_tablen(void **tab);

#endif /* HAJLIB_UTILS_H */