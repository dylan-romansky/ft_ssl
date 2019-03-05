/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 00:03:00 by dromansk          #+#    #+#             */
/*   Updated: 2019/01/11 19:08:25 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int n)
{
	int		i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char		*ft_itoa(int n)
{
	char	*s;
	long	v;
	int		i;
	int		c;

	v = n;
	i = (n < 0) ? numlen(n) + 1 : numlen(n);
	if ((s = ft_strnew(i)))
	{
		while (i--)
		{
			c = v % 10;
			s[i] = c < 0 ? -c + '0' : c + '0';
			v /= 10;
		}
		if (n < 0)
			s[0] = '-';
		return (s);
	}
	return (NULL);
}
