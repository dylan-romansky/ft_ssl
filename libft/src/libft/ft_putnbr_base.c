/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:57:59 by dromansk          #+#    #+#             */
/*   Updated: 2018/12/27 20:52:47 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int value, int base)
{
	long	n;

	if (base == 10)
		n = (long)value;
	else
		n = (unsigned int)value;
	if (n < 0)
	{
		if (base == 10)
			ft_putchar('-');
		n = -n;
	}
	if (n >= base)
	{
		ft_putnbr_base((int)(n / base), base);
		ft_putnbr_base((int)(n % base), base);
	}
	else
		ft_putchar(base_table((int)n));
}
