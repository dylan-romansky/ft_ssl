/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:32:12 by dromansk          #+#    #+#             */
/*   Updated: 2019/01/08 21:40:01 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	numlen_base(intmax_t n, int base)
{
	long		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char		*ft_ltoa_base(long long n, int base)
{
	char		*s;
	intmax_t	v;
	long		i;

	v = n;
	i = numlen_base(n, base);
	if (base == 10)
		return (ft_ltoa(n));
	if ((s = ft_strnew(i)))
	{
		if (v < 0)
		{
			s[0] = '0';
			i--;
		}
		s[i] = '\0';
		while (i--)
		{
			s[i] = base_table(v % base);
			v /= base;
		}
		return (s);
	}
	return (NULL);
}
