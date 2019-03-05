/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 14:19:16 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/04 14:14:39 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

intmax_t	get_normal(va_list *args)
{
	return (va_arg(*args, int));
}

intmax_t	get_h(va_list *args)
{
	int		s;

	s = (short)va_arg(*args, int);
	return (s);
}

intmax_t	get_hh(va_list *args)
{
	int		c;

	c = (char)va_arg(*args, int);
	return (c);
}
