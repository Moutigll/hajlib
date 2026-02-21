#ifndef HAJLIB_GF256_H
#define HAJLIB_GF256_H

#include <stdint.h>


/**
 * @brief Generic multiplication in GF(2^n) for arbitrary bit sizes.
 * @param a First operand
 * @param b Second operand
 * @param poly Irreducible polynomial for reduction (must be of degree n)
 * @param bits Number of bits in the field (e.g. 8 for GF(2^8))
 * @return Product of a and b in GF(2^n)
 */
uint64_t ft_gf2nMul(uint64_t a, uint64_t b, uint64_t poly, int bits);

/**
 * @brief Computes the power of an element in a Galois Field of size 2^n.
 * @param base The base element
 * @param exp The exponent
 * @param poly The irreducible polynomial defining the field
 * @param bits The number of bits in the field (e.g. 8 for GF(2^8))
 * @return The result of base raised to the power of exp in the Galois Field
 */
uint64_t ft_gf2nPow(uint64_t base, uint64_t exp, uint64_t poly, int bits);

/**
 * @brief Computes the multiplicative inverse of an element in a Galois Field of size 2^n.
 * @param x Element to invert
 * @param poly The irreducible polynomial defining the field
 * @param bits The number of bits in the field (e.g. 8 for GF(2^8))
 * @return The multiplicative inverse of x in the Galois Field, or 0 if x is 0
 */
uint64_t ft_gf2nInv(uint64_t x, uint64_t poly, int bits);

/**
 * @brief Applies an affine transformation to an element in a Galois Field of size 2^n.
 * @param x The input element
 * @param matrix The transformation matrix (should be bits x bits)
 * @param constant The constant to add after the linear transformation
 * @param bits The number of bits in the field (e.g. 8 for GF(2^8))
 * @return The result of the affine transformation applied to x
 */
uint64_t ft_gf2nAffine(uint64_t x, const uint64_t *matrix, uint64_t constant, int bits);

#endif /* HAJLIB_GF256_H */
