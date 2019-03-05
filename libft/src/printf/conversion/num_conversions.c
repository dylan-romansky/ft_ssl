/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 21:02:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/26 00:23:24 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

long	numlen(intmax_t n, int base)
{
	long		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char	*ft_imaxtoa_base(long long n, int base)
{
	char		*st;
	intmax_t	v;
	long		i;
	int			neg;

	v = n;
	neg = n < 0 ? 1 : 0;
	i = numlen(n, base);
	if ((st = ft_strnew(neg + i)))
	{
		st[i] = '\0';
		while (i--)
		{
			st[i + neg] = v < 0 ? base_table(-(v % base)) :
				base_table((v % base));
			v /= base;
		}
		if (neg)
			st[0] = '-';
		return (st);
	}
	return (NULL);
}

int		unumlen(uintmax_t value, unsigned int base)
{
	int			i;

	i = 1;
	while (value /= base)
		i++;
	return (i);
}

char	*ft_uimaxtoa_base(long long n, int base)
{
	char		*s;
	uintmax_t	v;
	long		i;

	v = n;
	i = unumlen(v, base);
	if ((s = ft_strnew(i)))
	{
		s[i] = '\0';
		while (i--)
		{
			s[i] = base_table((unsigned int)(v % base));
			v /= base;
		}
		return (s);
	}
	return (NULL);
}
