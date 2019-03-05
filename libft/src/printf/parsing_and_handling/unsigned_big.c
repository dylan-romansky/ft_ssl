/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 21:07:41 by dromansk          #+#    #+#             */
/*   Updated: 2019/01/30 21:09:26 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

intmax_t	uget_l(va_list *args)
{
	return ((unsigned long)va_arg(*args, long));
}

intmax_t	uget_ll(va_list *args)
{
	return ((unsigned long long)va_arg(*args, long long));
}

intmax_t	uget_j(va_list *args)
{
	return (va_arg(*args, intmax_t));
}

intmax_t	uget_z(va_list *args)
{
	return (va_arg(*args, ssize_t));
}
