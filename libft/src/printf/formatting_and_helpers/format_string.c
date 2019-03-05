/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:32:04 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/04 20:09:49 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "enums.h"

char	*handle_width(char *str, t_flag *flags, int t)
{
	char	*p;
	char	*n;
	int		len;

	if (str[0] == '-' && flags->zero)
		return (neg_width(str, flags, t));
	len = (t == ch) ? 1 : (int)ft_strlen(str);
	n = NULL;
	p = (flags->zero && !flags->dash && ((len < flags->prec && flags->dot) ||
				(!flags->dot || !flags->prec))) ?
		ft_strdup("0") : ft_strdup(" ");
	n = ft_strdup(str);
	while (len < flags->width)
	{
		if (flags->dash)
			n = swap_n_free((nullcheck(str)) ? ft_strjoin_len(n, p, len, 1) :
					ft_strjoin(n, p), &n);
		else
			n = swap_n_free(ft_strjoin(p, n), &n);
		len++;
	}
	free(p);
	return (n);
}

char	*handle_space(char *str, t_flag *flags)
{
	char	*nc;
	char	*n;

	n = ft_strdup(str);
	if (flags->zero)
		n = swap_n_free(space_z(str, flags), &n);
	nc = (flags->plus) ? ft_strdup("+") : ft_strdup(" ");
	if (str[0] != ' ' && str[0] != '-' && str[0] != '+')
	{
		n = swap_n_free(ft_strjoin(nc, n), &n);
	}
	free(nc);
	return (n);
}

char	*handle_precision(char *str, t_flag *flags, int ty)
{
	char	*t;
	char	*n;
	int		len;

	if (*str == '-')
		return (neg_prec(str, flags, ty));
	t = ft_strdup("0");
	n = ft_strdup(str);
	len = (int)ft_strlen(str);
	if (len > flags->prec && (ty == st || ft_strequ("0", str)))
		n = swap_n_free(ft_strndup(n, flags->prec), &n);
	if (len < flags->prec && ty != ch && ty != st)
		while (len < flags->prec)
		{
			n = swap_n_free(ft_strjoin(t, n), &n);
			len++;
		}
	free(t);
	return (n);
}

char	*alt(char *str, t_flag *flags, int t)
{
	char	*n;

	if ((t == x || t == X) && !ft_strlen(str))
		return (str);
	if (t != p && ft_strequ(str, "0"))
		return (ft_strdup(str));
	if (flags->zero)
		n = format_alt(str, flags, t);
	else
		n = ft_strdup(str);
	if (n[0] != '0' && (t == o || t == O))
		n = swap_n_free(ft_strjoin("0", n), &n);
	else if ((t == x || t == X || t == p) &&
			(ft_strlen(n) < 2 || !(n[1] == 'x' || n[1] == 'X')))
		n = swap_n_free(ft_strjoin("0x", n), &n);
	return (n);
}

int		format_string(char *st, t_flag *flags, char **buf, int t)
{
	char	*n;

	if ((t == F || t == f) && float_check(st))
	{
		if (t == F)
			st = ft_strupper(st);
		*buf = st;
		return (ft_strlen(st));
	}
	else
		n = ft_strdup(st);
	if (flags->dot && ((t != f && t != F && t != per) ||
				!(t == p && flags->prec == 0)))
		n = swap_n_free(handle_precision(n, flags, t), &n);
	if (flags->sharp || t == p)
		n = swap_n_free(alt(n, flags, t), &n);
	if ((flags->space || flags->plus) && (t == in || t == d))
		n = swap_n_free(handle_space(n, flags), &n);
	if (flags->width)
		n = swap_n_free(handle_width(n, flags, t), &n);
	if (t == X)
		n = ft_strupper(n);
	*buf = n;
	return (find_size(flags, n, t));
}
