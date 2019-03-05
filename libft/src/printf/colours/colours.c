/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 14:57:14 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/05 16:53:36 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "colours.h"

int		colour_skip(char *format)
{
	int		i;

	i = 0;
	while (format[i] && format[i] != '}')
		i++;
	return (i);
}

char	*colourcode(char *format)
{
	int		i;

	i = 0;
	while (format[i] && format[i] != '}')
		i++;
	return (ft_strndup(++format, --i));
}

int		colour(char *format)
{
	char	*code;
	int		i;

	i = 0;
	code = colourcode(format);
	while (i <= 6 && ft_strcmp(code, g_colour[i].colour))
		i++;
	return (i);
}

int		get_colour(char *format, char **buf)
{
	int		i;

	i = colour(format);
	if (i > 6)
	{
		*buf = ft_strndup(format, colour_skip(format) + 1);
		return (ft_strlen(*buf));
	}
	*buf = ft_strdup(g_colour[i].code);
	return (ft_strlen(g_colour[i].code));
}
