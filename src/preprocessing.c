/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:29:52 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/28 21:42:21 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void			split_input_512(char *input, int len)
{
	char			*process;
	int				i;
	int				j;
	char			*hash;
	int				c;

	hash = (char *)malloc(sizeof(char) * 16);
	process = ft_strdup(input);
	j = -1;
	c = 0;
	while (j < len)
	{
		i = -1;
		process = ft_strnew(64);
		while (input[++j] && ++i < 64)
			process[i] = input[j];
		hash = hashing(hash, process, c);
		free(process);
		c++;
	}
}

unsigned char	get_byte(int num)
{
	unsigned char	byte;
	unsigned char	i;

	i = 128;
	byte = 0;
	while (i)
	{
		if (i & num)
			byte |= 1;
		if (i != 1)
			byte <<= 1;
		i >>= 1;
	}
	return byte;
}

unsigned char	*get_bytes(int num)
{
	int				j;
	int				k;
	unsigned char	*bytes;

	j = 0;
	k = 0;
	bytes = (unsigned char *)malloc(sizeof(unsigned char) * 8);
	while (num)
	{
		bytes[j++] = get_byte(num);
		num >>= 8;
	}
	while (j < 8)
		bytes[j++] = bytes[k++];
	return (bytes);
}

char			*append_len(char *fixed, int i, long num)
{
	unsigned char	*bytes;
	int				j;

	bytes = get_bytes(num);
	j = 0;
	while (j < 8)
		fixed[i++] = bytes[j++];
	free(bytes);
	return (fixed);
}

void			pad_input(char *input)
{
	size_t			len;
	size_t			i;
	char			*fixed;

	len = ft_strlen(input);
	i = len;
	while ((i + 8) % 512 || (i + 8) < 512)
		i++;
	fixed = ft_strnew(i + 8);
	fixed = ft_strcpy(fixed, input);
	fixed[len] = 127;
	fixed = append_len(fixed, i, 4294967296 % len);
	ft_print_n(fixed, i + 8);
	split_input_512(input, i + 8);
}
