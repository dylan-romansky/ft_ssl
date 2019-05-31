/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:16:19 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/30 23:27:23 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	char_base(char c)
{
	if ('A' <= c && c <= 'Z')
		return (c - 'A');
	if ('a' <= c && c <= 'z')
		return (c - 'a' + 26);
	if (0 <= c && c <= '9')
		return (c - '0' + 52);
	if (c == '+')
		return (62);
	if (c == '/')
		return (63);
	return (0);
}

unsigned		remove_chars(unsigned chunk)
{
	unsigned char	*d;
	int				i;

	i = -1;
	d = (unsigned char *)ft_strnew(3);
	ft_memcpy(d, &chunk, 4);
	while (++i < 4)
		d[i] = char_base(d[i]);
	ft_memcpy(&chunk, d, 4);
	free(d);
	return (chunk);
}

unsigned char	*expand_base(unsigned chunk)
{
	unsigned char	bytes[3];
	unsigned char	*expanded;

	expanded = (unsigned char *)ft_strnew(3);
	ft_memcpy(bytes, &chunk, 3);
	expanded[0] = (bytes[0] & 252) >> 2;
	expanded[1] = ((bytes[0] & 3) << 4) | bytes[1] >> 4;
	expanded[2] = ((bytes[1] & 15) << 2) | bytes[2] >> 6;
	expanded[3] = bytes[2] & 63;
	return (expanded);
}

unsigned char	*contract_base(unsigned chunk)
{
	unsigned char	expanded[4];
	unsigned char	*contracted;

	contracted = (unsigned char *)ft_strnew(2);
	chunk = remove_chars(chunk);
	ft_memcpy(expanded, &chunk, 4);
	contracted[0] = (expanded[0] << 2) | (expanded[1] >> 4);
	contracted[1] = (expanded[1] << 4) | (expanded[2] >> 2);
	contracted[2] = (expanded[2] << 6) | expanded[3];
	return (contracted);
}
