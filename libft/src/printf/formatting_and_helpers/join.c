/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:12:22 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/04 20:10:18 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "enums.h"

char	*neg_width(char *s, t_flag *flags, int t)
{
	char *neg;
	char *dig;

	neg = ft_strdup("-");
	flags->width -= 1;
	dig = handle_width(s + 1, flags, t);
	flags->width += 1;
	return (ft_strjoin(neg, dig));
}

char	*force_copy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*joining(char **string, char **buf, int len, int buflen)
{
	char	*new;

	if (!(string && *string))
		return (*buf);
	if (!(new = ft_strnew(len + buflen)))
		return (NULL);
	new = force_copy(new, *string, len);
	new = (force_copy(new + len, *buf, buflen) - len);
	free(*string);
	free(*buf);
	return (new);
}

int		find_size(t_flag *flags, char *str, int t)
{
	int		len;

	len = (int)ft_strlen(str);
	if ((len > flags->prec && len > flags->width) || t == st)
		return (len);
	else if (flags->dot && flags->prec > flags->width && t != f && t != ch)
		return (flags->prec);
	else if ((!flags->dot && flags->width) || (flags->prec < flags->width))
		return (flags->width);
	if (t == ch)
		return (1);
	return (0);
}

int		nullcheck(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\0')
			return (0);
	return (1);
}
