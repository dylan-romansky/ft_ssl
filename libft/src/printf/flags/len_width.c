/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 15:12:25 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/28 16:56:40 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "typestruct.h"
#include "enums.h"

void	get_width(char *format, va_list *args, t_flag **flags)
{
	if (*format >= '0' && *format <= '9')
	{
		(*flags)->width = ft_atoi(format);
		while ('0' <= *format && *format <= '9')
			format++;
	}
	if (*format == '*')
	{
		(*flags)->width = va_arg(*args, int);
		format++;
	}
	if (*format >= '0' && *format <= '9')
		(*flags)->width = ft_atoi(format);
	if ((*flags)->width < 0)
	{
		(*flags)->dash = 1;
		(*flags)->width = -((*flags)->width);
	}
}

int		set_width(t_flag **input, char *format, va_list *args)
{
	t_flag	*flags;

	flags = *input;
	while (*format && (('0' <= *format && *format <= '9') ||
				*format == '*' || *format == '.'))
	{
		if (('0' <= *format && *format <= '9') || *format == '*')
		{
			get_width(format, args, &flags);
			format += skip_nums(format);
		}
		if (*format == '.')
			format += prec(format, args, input);
		if (*format == '-')
			flags->dash = 1;
		if (*format == ' ')
			flags->space = 1;
		if (*format == '#')
			flags->sharp = 1;
		if (!(*format && (('0' <= *format && *format <= '9') ||
						*format == '*' || *format == '.')))
			break ;
		format++;
	}
	return (1);
}

int		set_length(t_flag **input, char *format)
{
	t_flag	*flags;

	flags = *input;
	if (*format == 'l' && *(format + 1) == 'l')
		flags->size = ll;
	else if (*format == 'l' && *(format + 1) != 'l')
		flags->size = l;
	if (*format == 'h' && *(format + 1) == 'h')
		flags->size = hh;
	else if (*format == 'h' && *(format + 1) != 'h')
		flags->size = h;
	if (*format == 'z')
		flags->size = z;
	if (*format == 'L')
		flags->size = el;
	if (*format == 'j')
		flags->size = j;
	return (1);
}

int		set_type(t_flag **input, char *format)
{
	int		i;
	t_flag	*flags;

	flags = *input;
	i = 0;
	if (!check_flag(format))
	{
		flags->type = ch;
		return (1);
	}
	else
	{
		format += flag_skip(format);
		while (g_types[i].type != *format)
			i++;
		flags->type = g_types[i].num;
		if (ft_isupper(g_types[i].type) && l != flags->size &&
				ll != flags->size && flags->type != X)
			flags->size = l;
		if (g_types[i].type == 'b')
			fix_bin(&flags);
		return (1);
	}
	return (0);
}
