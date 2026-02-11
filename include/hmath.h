#ifndef HAJLIB_MATH_H
# define HAJLIB_MATH_H

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
 * @brief Calculates the square root of a number using the Newton's method.
 * @param x - number to calculate the square root of
 * @return square root of x, or -1 if x is negative
 */
double	ft_sqrtNewton(double x);

#endif	/* HAJLIB_MATH_H */