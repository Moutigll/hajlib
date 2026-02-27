#ifndef HAJLIB_CHAR_H
#define HAJLIB_CHAR_H

/**
 * @brief Converts a character to its corresponding digit value in a given base.
 * For example, '0' to '9' will be converted to 0-9, 'A' to 'Z' will be converted to 10-35, and 'a' to 'z' will also be converted to 10-35.
 * If the character is not a valid digit in the specified base, the function returns -1.
 * @param c The character to convert.
 * @param base The numerical base (e.g., 10 for decimal, 16 for hexadecimal).
 * @return The digit value of the character if it is valid for the given base, or -1 if it is not a valid digit.
 */
int	ft_charToDigit(int c, int base);

/**
 * @brief Checks if the character is alphanumeric (letter or digit).
 * @param c - The character to check.
 * @return 1 if `c` is alphanumeric, 0 otherwise.
 */
int	ft_isalnum(int c);

/**
 * @brief Checks if the character is an alphabetic letter (either uppercase or lowercase).
 * @param c - The character to check.
 * @return 1 if `c` is an alphabetic letter, 0 otherwise.
 */
int	ft_isalpha(int c);

/**
 * @brief Checks if the character is a whitespace character (space, tab, newline, etc.).
 * @param c - The character to check.
 * @return 1 if `c` is a whitespace character, 0 otherwise.
 */
int	ft_isascii(int c);

/**
 * @brief Checks if the character is a digit (0-9).
 * @param c - The character to check.
 * @return 1 if `c` is a digit (0-9), 0 otherwise.
 */
int	ft_isdigit(int c);

/**
 * @brief Checks if the character is printable (including space).
 * @param c - The character to check.
 * @return 1 if `c` is printable, 0 otherwise.
 */
int	ft_isprint(int c);

/**
 * @brief Checks if the character is a whitespace character (space, tab, newline, etc.).
 * @param c - The character to check.
 * @return 1 if `c` is a whitespace character, 0 otherwise.
 */
int	ft_isspace(int c);

/**
 * @brief Converts the character to lowercase if it is uppercase.
 * @param c - The character to convert.
 * @return The lowercase equivalent of `c` if it is uppercase, otherwise returns `c` unchanged.
 */
int	ft_tolower(int c);

/**
 * @brief Converts the character to uppercase if it is lowercase.
 * @param c - The character to convert.
 * @return The uppercase equivalent of `c` if it is lowercase, otherwise returns `c` unchanged.
 */
int	ft_toupper(int c);

#endif	/* HAJLIB_CHAR_H */
