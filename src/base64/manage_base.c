/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:16:19 by dromansk          #+#    #+#             */
/*   Updated: 2019/06/04 18:51:54 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const char	*g_base = {
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

void			char_swap(unsigned char *chunk, int p)
{
	int				size;
	int				i;

	size = 4;
	i = 0;
	while (size-- > p)
	{
		chunk[i] = g_base[(int)chunk[i]];
		i++;
	}
	while (p-- > 0)
		chunk[i++] = '=';
}

unsigned char	char_base(char c)
{
	if ('A' <= c && c <= 'Z')
		return (c - 'A');
	else if ('a' <= c && c <= 'z')
		return (c - 'a' + 26);
	else if ('0' <= c && c <= '9')
		return (c - '0' + 52);
	else if (c == '+')
		return (62);
	else if (c == '/')
		return (63);
	return (0);
}

unsigned		remove_chars(unsigned chunk)
{
	unsigned char	d[4];
	int				i;

	i = -1;
	ft_memcpy(d, &chunk, 4);
	while (++i < 4)
		d[i] = char_base(d[i]);
	ft_memcpy(&chunk, d, 4);
	return (chunk);
}

void			expand_base(unsigned chunk, unsigned char *e)
{
	unsigned char	bytes[3];

	ft_memcpy(bytes, &chunk, 3);
	e[0] = (bytes[0] & 252) >> 2;
	e[1] = ((bytes[0] & 3) << 4) | bytes[1] >> 4;
	e[2] = ((bytes[1] & 15) << 2) | bytes[2] >> 6;
	e[3] = bytes[2] & 63;
}

void			contract_base(unsigned chunk, unsigned char *d)
{
	unsigned char	expanded[4];

	chunk = remove_chars(chunk);
	ft_memcpy(expanded, &chunk, 4);
	d[0] = (expanded[0] << 2) | (expanded[1] >> 4);
	d[1] = (expanded[1] << 4) | (expanded[2] >> 2);
	d[2] = (expanded[2] << 6) | expanded[3];
}
