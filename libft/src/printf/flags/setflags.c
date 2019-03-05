/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setflags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 14:04:16 by dromansk          #+#    #+#             */
/*   Updated: 2019/01/29 18:19:02 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "enums.h"

int		set_flags(t_flag **flags, char *format, va_list *args)
{
	if (is_flag(*format, "- 0#+"))
	{
		if (!set_first(flags, format))
			return (0);
		while (is_flag(*format, "- 0#+"))
		{
			if (*format == '0' && *(format + 1) != '0')
				format++;
			else if (*format == '0' && *(format + 1) == '0')
			{
				format++;
				break ;
			}
			else
				format++;
		}
	}
	return (set_more_flags(flags, format, args));
}

int		set_first(t_flag **input, char *format)
{
	t_flag	*flags;

	flags = *input;
	while (is_flag(*format, "- 0#+"))
	{
		if (*format == '-')
			flags->dash = 1;
		if (*format == ' ')
			flags->space = 1;
		if (*format == '0')
			flags->zero = 1;
		if (*format == '#')
			flags->sharp = 1;
		if (*format == '+')
			flags->plus = 1;
		format++;
	}
	return (1);
}

int		set_more_flags(t_flag **flags, char *format, va_list *args)
{
	if (is_flag(*format, "*.0123456789"))
	{
		if (!set_width(flags, format, args))
			return (0);
		while (is_flag(*format, "*.0123456789"))
			format++;
	}
	if (is_flag(*format, "hlLjz"))
	{
		if (!set_length(flags, format++))
			return (0);
	}
	if (!set_type(flags, format))
		return (0);
	return (1);
}

int		prec(char *format, va_list *args, t_flag **input)
{
	t_flag	*flags;
	int		i;

	flags = *input;
	flags->dot = 1;
	i = 1;
	if (format[i] >= '0' && format[i] <= '9')
	{
		flags->prec = ft_atoi(format + i);
		i += skip_nums(format + i);
	}
	if (format[i] == '*')
	{
		flags->prec = va_arg(*args, int);
		i++;
	}
	if (format[i] >= '0' && format[i] <= '9')
		flags->prec = ft_atoi(format + i);
	if (flags->prec < 0)
	{
		flags->dot = 0;
		flags->prec = 0;
	}
	return (skip_nums(format + i) + i);
}
