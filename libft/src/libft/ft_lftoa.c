/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lftoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:50:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/01/08 20:12:55 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	precision(long double dec, size_t prec)
{
	while (prec--)
		dec *= 10;
	return ((long long)(dec + 0.5));
}

int			nan_comp(long double f)
{
	float		test;

	test = 0;
	if (!(f >= test) && !(f <= test))
		return (1);
	return (0);
}

char		*ft_lftoa(long double f, size_t prec)
{
	long long	num;
	long long	dec;
	char		*s;

	if (f < LDBL_MIN || f > LDBL_MAX)
		return (ft_strdup("inf"));
	if (nan_comp(f))
		return (ft_strdup("nan"));
	num = (long long)f;
	s = ft_ltoa_base(num, 10);
	dec = precision((f - num), prec);
	if (dec)
	{
		s = ft_strjoin(s, ".");
		if (dec < 0)
			dec = -dec;
		s = ft_strjoin(s, ft_ltoa_base(dec, 10));
	}
	return (s);
}
