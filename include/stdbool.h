/**
 * @file stdbool.h
 * @brief Boolean type and values.
 *
 * This header defines bool, true, false, and
 * __bool_true_false_are_defined, as specified by the C standard.
 *
 * In C23, bool, true, and false are keywords and this header
 * is no longer necessary. We still provide it for compatibility
 * with C11 and C17.
 */

#ifndef _STDBOOL_H
# define _STDBOOL_H

# if __STDC_VERSION__ >= 202311L
/*
 * C23 and later: bool, true, and false are keywords. Do not
 * redefine them. This header only needs to define the
 * __bool_true_false_are_defined macro for compatibility.
 */
#  ifndef __bool_true_false_are_defined
#   define __bool_true_false_are_defined 1
#  endif
# else
/*
 * C11 and C17: bool is a macro that expands to _Bool (a real
 * type), and true/false are macros that expand to 1 and 0.
 */
#  ifndef __bool_true_false_are_defined
#   define __bool_true_false_are_defined 1

#   define bool	_Bool
#   define true		1
#   define false	0
#  endif
# endif

#endif /* _STDBOOL_H */
