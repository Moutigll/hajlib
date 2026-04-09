/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:44:33 by moutig            #+#    #+#             */
/*   Updated: 2026/04/09 15:45:04 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int ft_log2(uint64_t x)
{
    if (x == 0)
        return (0);
    
#if defined(__GNUC__) || defined(__clang__)
    /* Use compiler builtin (1 instruction on most CPUs) */
    return (63 - __builtin_clzll(x));
#else
    /* Fallback: manual binary search (pure C, works everywhere) */
    int result = 0;
    
    if (x >= (uint64_t)1 << 32)
    {
        x >>= 32;
        result += 32;
    }
    if (x >= (uint64_t)1 << 16)
    {
        x >>= 16;
        result += 16;
    }
    if (x >= (uint64_t)1 << 8)
    {
        x >>= 8;
        result += 8;
    }
    if (x >= (uint64_t)1 << 4)
    {
        x >>= 4;
        result += 4;
    }
    if (x >= (uint64_t)1 << 2)
    {
        x >>= 2;
        result += 2;
    }
    if (x >= (uint64_t)1 << 1)
    {
        x >>= 1;
        result += 1;
    }
    
    return (result);
#endif
}
