/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:16:47 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/30 23:50:03 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	*char_swap(unsigned char *chunk, int p)
{
	int				size;
	int				i;
	unsigned char	*s;

	size = 4;
	i = 0;
	s = (unsigned char *)ft_strnew(4);
	while (size-- > p)
	{
		if (*chunk < 26)
			s[i] = 'A' + *chunk;
		else if (*chunk < 52)
			s[i] = 'a' + (*chunk - 26);
		else if (*chunk < 62)
			s[i] = '0' + (*chunk - 52);
		else if (*chunk < 64)
			s[i] = (*chunk - 62) ? '/' : '+';
		chunk++;
		i++;
	}
	while (p-- > 0)
		s[i++] = '=';
	return (s);
}

unsigned		get_chunk(char *input, int i, int len, int size)
{
	unsigned		chunk;

	chunk = 0;
	if (i < (len - size - 1))
		ft_memcpy(&chunk, input + i, size);
	else
		ft_memcpy(&chunk, input + i, len - i);
	return (chunk);
}

unsigned char	*ft_base64_e(char *input, size_t len)
{
	int				chunk;
	size_t			i;
	unsigned char	*e;
	unsigned char	*s;

	chunk = 0;
	i = 0;
	s = (unsigned char *)ft_strnew(0);
	while (i < len)
	{
		chunk = get_chunk(input, i, len, i < len - 2 ? 3 : len - i);
		e = expand_base(chunk);
		i += 3;
		char_swap(e, i > len ? i - len : 0);
		s = (unsigned char *)ft_hardjoin((char *)s, (4 * ((i - 3 / 3))),
				(char *)e, i > len ? (i - len) : 4);
	}
	return (s);
}

unsigned char	*ft_base64_d(char *input, size_t len)
{
	int				chunk;
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	chunk = 0;
	i = 4;
	len -= minus_pad(input);
	s = (unsigned char *)ft_strnew(0);
	while (i < len)
	{
		chunk = get_chunk(input, i, len, i < len - 3 ? 4 : len - i);
		d = contract_base(chunk);
		i += 4;
		s = (unsigned char *)ft_hardjoin((char *)s, (3 * ((i - 4) / 4)),
				(char *)d, i > len ? (i - len) : 3);
	}
	return (s);
}
