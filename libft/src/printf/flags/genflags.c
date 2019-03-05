/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genflags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:18:32 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/05 16:48:22 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "enums.h"

int		skip_nums(char *format)
{
	int			i;

	i = 0;
	while (('0' <= format[i] && format[i] <= '9') || format[i] == '*')
		i++;
	return (i);
}

int		flag_skip(char *format)
{
	int		i;

	i = 0;
	if (*(format - 1) == '{')
		return (colour_skip(format));
	while (is_flag(format[i], "+ 0123456789#hlLzj.-*"))
		i++;
	return (i);
}

void	flag_del(t_flag **flags)
{
	if (initflags(flags))
		free(*flags);
}

int		initflags(t_flag **input)
{
	t_flag	*new;

	new = *input;
	if (new != NULL)
	{
		new->sharp = 0;
		new->zero = 0;
		new->dash = 0;
		new->plus = 0;
		new->space = 0;
		new->dot = 0;
		new->prec = 0;
		new->width = 0;
		new->size = 0;
		new->type = 0;
		return (1);
	}
	return (0);
}

int		is_flag(char form, char *flags)
{
	while (*flags && form != *flags)
		flags++;
	if (*flags == form)
		return (1);
	return (0);
}
