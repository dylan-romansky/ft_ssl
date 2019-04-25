/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:15:26 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/31 00:45:54 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	get_prec(int precision)
{
	long double d;

	d = 1;
	while (precision--)
		d /= 10;
	return (d);
}

long double	ft_sqrt(int square, int precision)
{
	long double integer;
	long double decimal;

	integer = 0;
	decimal = get_prec(precision);
	while (integer * integer <= square)
		integer++;
	integer--;
	while (integer * integer < square)
		integer += decimal;
	return (integer);
}
