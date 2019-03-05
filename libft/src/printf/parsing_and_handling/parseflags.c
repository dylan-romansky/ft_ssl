/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseflags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:50:27 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/05 13:32:12 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "printstruct.h"
#include "enums.h"

int		parse_arg(t_flag *flags, va_list *args, char **buf)
{
	int			i;
	char		*data;

	i = convert_type_num(flags->type);
	if (i == 4)
	{
		flags->type = ch;
		return (format_string("%", flags, buf, ch));
	}
	data = g_string[i].string(flags, args);
	if (!data)
		data = null_cases(flags->type);
	i = format_string(data, flags, buf, flags->type);
	free(data);
	return (i);
}

char	*parse_numbers(t_flag *flags, va_list *args)
{
	intmax_t	num;
	int			base;

	if (flags->type == d)
		num = g_arglen[flags->size].parse(args);
	else
		num = g_uarglen[flags->size].parse(args);
	base = g_numconvert[flags->type].base;
	return (g_numconvert[flags->type].data(num, base));
}

char	*parse_chars(t_flag *flags, va_list *args)
{
	int			i;

	i = flags->type - 7;
	if (!i)
		return (get_string(args));
	return (get_char(args));
}

char	*parse_float(t_flag *flags, va_list *args)
{
	long double	f;

	if (flags->size == el)
		f = va_arg(*args, long double);
	else
		f = va_arg(*args, double);
	if (!flags->dot)
	{
		flags->dot = 1;
		flags->prec = 6;
	}
	return (ft_ftoa(f, flags->prec));
}

char	*parse_pointer(t_flag *flags, va_list *args)
{
	size_t		ptr;
	void		*st;

	st = va_arg(*args, void *);
	flags->type = p;
	if (!st)
		return (NULL);
	ptr = (size_t)st;
	return (ft_ltoa_base(ptr, 16));
}
