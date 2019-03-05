/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:06:38 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/05 13:34:06 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "enums.h"

char	*space_z(char *str, t_flag *flags)
{
	char	*n;

	flags->width -= 1;
	n = handle_width(str, flags, flags->type);
	flags->width += 1;
	return (n);
}

char	*format_alt(char *st, t_flag *flags, int t)
{
	char	*n;

	n = st;
	if (t == x || t == X || t == p)
	{
		flags->width -= 2;
		n = handle_width(st, flags, t);
		flags->width += 2;
	}
	else if (t == o)
	{
		flags->width -= 1;
		n = handle_width(st, flags, t);
		flags->width += 1;
	}
	return (n);
}

char	*neg_prec(char *st, t_flag *flags, int t)
{
	char	*neg;
	char	*dig;
	char	*ret;

	dig = ft_strsub(st, 1, (int)ft_strlen(st) - 1);
	neg = ft_strdup("-");
	dig = swap_n_free(handle_precision(dig, flags, t), &dig);
	ret = ft_strjoin(neg, dig);
	free(dig);
	free(neg);
	return (ret);
}
