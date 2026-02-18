#ifndef HAJLIB_STRING_H
# define HAJLIB_STRING_H

#include <stdlib.h>

/**
 * @brief Splits a string into an array of strings using a delimiter character.
 * @param s - The string to split.
 * @param c - The delimiter character.
 * @return A NULL-terminated array of strings resulting from the split. The caller is responsible for freeing the memory.
 */
char	**ft_split(char const *s, char c);

/**
 * @brief Replaces all occurrences of a substring in a string with another substring.
 * @param str - The string to search within.
 * @param to_replace - The substring to replace.
 * @param replacement - The substring to replace with.
 * @return A new string with all occurrences of `to_replace` replaced by `replacement`. The caller is responsible for freeing the memory.
 */
char	*ft_str_replace(char *str, char *to_replace, char *replacement);

/**
 * @brief Locates the first occurrence of a character in a string.
 * @param s - The string to search within.
 * @param c - The character to locate.
 * @return A pointer to the first occurrence of `c` in `s`, or NULL if `c` is not found. The terminating null byte is considered part of the string, so if `c` is `\0`, the function returns a pointer to the terminator.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Compares two strings lexicographically.
 * @param s1 - The first string to compare.
 * @param s2 - The second string to compare.
 * @return An integer less than, equal to, or greater than zero if `s1` is found, respectively, to be less than, to match, or be greater than `s2`. The comparison is done using unsigned characters, so that `\200` is greater than `\0`.
 */
int		ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Cuts a string at the first occurrence of a specified character, replacing it with a null terminator.
 * @param str - The string to cut. This string will be modified in place.
 * @param c - The character at which to cut the string.
 * @return A pointer to the original string, now truncated at the first occurrence of `c`. If `c` is not found, the original string is returned unchanged.
 */
char	*ft_strcut(char *str, char c);

/**
 * @brief Duplicates a string by allocating memory and copying the contents.
 * @param src - The string to duplicate.
 * @return A pointer to a new string which is a duplicate of `src`. The caller is responsible for freeing the memory. If memory allocation fails, NULL is returned.
 */
char	*ft_strdup(const char *src);

/**
 * @brief Applies a function to each character of a string, passing the index and a pointer to the character.
 * @param s - The string to iterate over. This string will be modified in place.
 * @param f - The function to apply to each character. It takes the index of the character and a pointer to the character itself.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief Joins two strings into a new string, with optional freeing of the input strings.
 * @param s1 - The first string to join. This string may be freed if `free_s1` is non-zero.
 * @param s2 - The second string to join. This string may be freed if `free_s2` is non-zero.
 * @param free_s1 - If non-zero, `s1` will be freed after being joined.
 * @param free_s2 - If non-zero, `s2` will be freed after being joined.
 * @return A new string that is the result of concatenating `s1` and `s2`. The caller is responsible for freeing the memory. If memory allocation fails, NULL is returned.
 */
char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);

/**
 * @brief Joins two strings into a new string.
 * @param s1 - The first string to join.
 * @param s2 - The second string to join.
 * @return A new string that is the result of concatenating `s1` and `s2`. The caller is responsible for freeing the memory. If memory allocation fails, NULL is returned.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Appends a string to the end of another string, ensuring that the total length does not exceed a specified buffer size. The result is always null-terminated (unless `dstsize` is 0 or the original `dst` string was longer than `dstsize`).
 * @param dst - The destination string to which `src` will be appended. This string must have enough allocated space to hold the result.
 * @param src - The string to copy from.
 * @param dstsize - The total size of the destination buffer, including the null terminator. This function will append at most `dstsize - strlen(dst) - 1` characters from `src`, and will always null-terminate the result (unless `dstsize` is 0 or the original `dst` string was longer than `dstsize`).
 * @return The total length of the string it tried to create, which is the initial length of `dst` plus the length of `src`. If the return value is greater than or equal to `dstsize`, truncation occurred.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @brief Copies a string to a destination buffer, ensuring that the total length does not exceed a specified buffer size. The result is always null-terminated (unless `dstsize` is 0).
 * @param dst - The destination buffer to which `src` will be copied. This buffer must have enough allocated space to hold the result.
 * @param src - The string to copy from.
 * @param dstsize - The total size of the destination buffer, including the null terminator. This function will copy at most `dstsize - 1` characters from `src`, and will always null-terminate the result (unless `dstsize` is 0).
 * @return The total length of the string it tried to create, which is the length of `src`. If the return value is greater than or equal to `dstsize`, truncation occurred.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @brief Returns the length of a string.
 * @param s - The string whose length is to be calculated.
 * @return The length of the string. The length is defined as the number of characters that precede the terminating null byte (`\0`).
 */
size_t	ft_strlen(const char *s);

/**
 * @brief Applies a function to each character of a string, passing the index and the character value, and creates a new string from the results.
 * @param s - The string to iterate over.
 * @param f - The function to apply to each character. It takes the index of the character and the character itself, and returns a new character.
 * @return A new string resulting from applying `f` to each character of `s`. The caller is responsible for freeing the memory. If memory allocation fails, NULL is returned.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Locates the last occurrence of a character in a string.
 * @param s - The string to search within.
 * @param c - The character to locate.
 * @return A pointer to the last occurrence of `c` in `s`, or NULL if `c` is not found. The terminating null byte is considered part of the string, so if `c` is `\0`, the function returns a pointer to the terminator.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Duplicates a string up to a specified length by allocating memory and copying the contents.
 * @param s - The string to duplicate.
 * @param n - The maximum number of characters to duplicate from `s`. If `s` is shorter than `n`, the entire string is duplicated.
 * @return A pointer to a new string which is a duplicate of the first `n` characters of `s`, null-terminated. The caller is responsible for freeing the memory. If memory allocation fails, NULL is returned.
 */
char	*ft_strndup(const char *s, size_t n);

/**
 * @brief Locates the first occurrence of a substring in a string, where not more than `len` characters are searched.
 * @param haystack - The string to search within.
 * @param needle - The substring to locate.
 * @param len - The maximum number of characters to search.
 * @return A pointer to the first occurrence of `needle` in `haystack`, or NULL if `needle` is not found within the first `len` characters.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/**
 * @brief Finds the first occurrence of a character in a string.
 * @param str - The string to search within.
 * @param c - The character to locate.
 * @return The index of the first occurrence of `c` in `str`, or -1 if `c` is not found.
 */
int		ft_strpos(const char *str, char c);

/**
 * @brief Locates the last occurrence of a character in a string.
 * @param s - The string to search within.
 * @param c - The character to locate.
 * @return A pointer to the last occurrence of `c` in `s`, or NULL if `c` is not found.
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief Locates the first occurrence of a substring in a string.
 * @param haystack - The string to search within.
 * @param needle - The substring to locate.
 * @return A pointer to the first occurrence of `needle` in `haystack`, or NULL if `needle` is not found.
 */
char	*ft_strstr(char *haystack, char *needle);

/**
 * @brief Trims characters from the beginning and end of a string.
 * @param s1 - The string to trim.
 * @param set - The set of characters to trim.
 * @return A new string with the characters in `set` removed from the beginning and end of `s1`. The caller is responsible for freeing the memory. If memory allocation fails, NULL is returned.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Extracts a substring from a string.
 * @param s - The string to extract from.
 * @param start - The starting index of the substring.
 * @param len - The length of the substring.
 * @return A new string containing the substring of `s` starting at `start` and of length `len`. The caller is responsible for freeing the memory. If memory allocation fails, NULL is returned.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif	/* HAJLIB_STRING_H */
