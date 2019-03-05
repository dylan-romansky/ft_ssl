/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 18:32:37 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/04 20:06:20 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "enums.h"

int		check_flag(char *format)
{
	while (*format && is_flag(*format, "-+ 0123456789#hlLzj.*"))
		format++;
	if (!is_flag(*format, "diuoxXcspf%UbODF"))
		return (0);
	return (1);
}

int		error_handle(char **buf)
{
	*buf = ft_strdup("");
	return (0);
}

char	*null_cases(int t)
{
	if (t == st)
		return (ft_strdup("(null)"));
	if (t == p)
		return (ft_strdup("0"));
	return (NULL);
}
