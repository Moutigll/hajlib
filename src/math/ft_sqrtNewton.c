/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrtNewton.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:44:10 by moutig            #+#    #+#             */
/*   Updated: 2026/02/11 16:50:44 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_sqrtNewton(double x)
{
	double	current;	/* current approximation */
	double	previous;	/* previous approximation */
	double	epsilon;	/* acceptable error margin */

	if (x < 0)	/* invalid input */
		return (-1);
	if (x == 0 || x == 1)
		return (x);
	epsilon = 0.000001;
	current = x;
	previous = 0;
	while (current - previous > epsilon || previous - current > epsilon)	/* while |current - previous| > epsilon */
	{
		previous = current;
		current = (current + x / current) / 2;	/* y = (y + x/y) / 2 */
	}
	return (current);
}
