/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:33:12 by dromansk          #+#    #+#             */
/*   Updated: 2019/01/29 15:06:49 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

int		ft_printf(const char *restrict format, ...)
{
	va_list args;
	int		printed;

	va_start(args, format);
	printed = make_string(format, &args, 1);
	va_end(args);
	return (printed);
}

int		ft_dprintf(int fd, const char *restrict format, ...)
{
	va_list args;
	int		printed;

	va_start(args, format);
	printed = make_string(format, &args, fd);
	va_end(args);
	return (printed);
}
