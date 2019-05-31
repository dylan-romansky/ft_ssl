/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 18:22:57 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/30 19:06:12 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_bin(unsigned long num, int size)
{
	int				i;
	unsigned long	p;

	p = (unsigned long)1 << (size - 1);
	i = -1;
	while (++i < size)
	{
		if (!(i % 8) && i != 0)
			ft_printf(" ");
		ft_printf("%d", p & num ? 1 : 0);
		p >>= 1;
	}
	ft_printf("\n");
}
