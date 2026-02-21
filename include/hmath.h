#ifndef HAJLIB_MATH_H
# define HAJLIB_MATH_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Converts a string representing a number in a given base to an integer.
 * @param str - string to convert
 * @param base - base to convert to
 * @return integer value of the string in the given base
 */
int		ft_atoi_base(char *str, char *base);

/**
 * @brief Converts a string to an integer.
 * @param str - string to convert
 * @return integer value of the string
 */
int		ft_atoi(const char *str);

/**
 * @brief Gets the sign of a number represented as a string.
 * @param str - pointer to the string to check
 * @return 1 if positive, -1 if negative
 */
int		get_sign(const char **str);

/**
 * @brief Converts a string to a long integer.
 * @param str - string to convert
 * @return long integer value of the string
 */
long	ft_atol(const char *str);

/**
 * @brief Calculates the cube root of a double using the Newton-Raphson method.
 * @param x - double to calculate the cube root of
 * @return cube root of x
 */
double	ft_cbrt(double x);

/**
 * @brief Converts an integer to a string.
 * @param n - integer to convert
 * @return string representation of the integer
 */
char	*ft_itoa(int n);

/**
 * @brief Converts a double to a string with specified precision.
 * @param n - double to convert
 * @param precision - number of decimal places
 * @return string representation of the double
 */
char	*ft_dtoa(double n, int precision);

/**
 * @brief Calculates the absolute value of a double.
 * @param x - double to calculate absolute value for
 * @return absolute value of x
 */
double ft_fabs(double x);

/**
* @brief Calculates the number of digits needed to represent an unsigned integer in a given base.
* @param n - unsigned integer to calculate length for
* @param base - base to use for calculation
* @return number of digits needed to represent n in the given base
*/
size_t	ft_numlen(unsigned int n, unsigned int base);

/**
 * @brief Calculates the power of a base raised to an exponent.
 * @param base - base value
 * @param exp - exponent value
 * @return result of base raised to the power of exp
 */
double	ft_pow(double base, double exp);

/**
 * @brief Calculates the sine of a double ( x in radians) using a Taylor series expansion.
 * @param x - double to calculate sine for
 * @return sine of x
 */
double ft_sin(double x);

/**
 * @brief Calculates the square root of a number using the Newton's method.
 * @param x - number to calculate the square root of
 * @return square root of x, or -1 if x is negative
 */
double	ft_sqrtNewton(double x);

/**
 * @brief Converts a string to a double.
 * @param str - string to convert
 * @param endptr - pointer to a pointer that will be set to the character after the last character used in the conversion
 * @return double value of the string
 */
double	ft_strtod(const char *str, char **endptr);

/**
 * @brief Converts a string to an unsigned long integer.
 * @param str - string to convert
 * @param endptr - pointer to a pointer that will be set to the character after the last character used in the conversion
 * @param base - base to convert to
 * @return unsigned long integer value of the string
 */
unsigned long	ft_strtoul(const char *str, char **endptr, int base);

/**
 * @brief Converts an unsigned integer to a string.
 * @param n - unsigned integer to convert
 * @return string representation of the unsigned integer
 */
char	*ft_utoa(unsigned int n);

/**
 * @brief Converts an unsigned integer to a string in a specified base.
 * @param n - unsigned integer to convert
 * @param base - base to convert to (e.g., 10 for decimal, 16 for hexadecimal)
 * @param upper - if non-zero, use uppercase letters for bases > 10
 * @return string representation of the unsigned integer in the specified base
 */
char	*ft_utoa_base(uintptr_t value, int base, int upper);

#endif	/* HAJLIB_MATH_H */
