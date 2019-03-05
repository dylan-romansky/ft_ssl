/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 20:32:12 by dromansk          #+#    #+#             */
/*   Updated: 2019/01/16 13:30:34 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen_base(int n, int base)
{
	int		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char		*ft_itoa_base(int n, int base)
{
	char	*s;
	long	v;
	int		i;

	if (base == 10)
		return (ft_itoa(n));
	v = n;
	i = numlen_base(n, base);
	if ((s = ft_strnew(i)))
	{
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
