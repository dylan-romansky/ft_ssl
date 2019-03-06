/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:29:52 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/05 18:18:33 by dromansk         ###   ########.fr       */
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

int				padding(char *input)
{
	size_t			len;
	size_t			i;
	char			*fixed;

	words->a0 = 0x67452301;
	words->b0 = 0xefcdab89;
	words->c0 = 0x98badcfe;
	words->d0 = 0x10325476;
	words->offset = 0;
	len = ft_strlen(input);
	i = len;
	while ((i + 8) % 512 || (i + 8) < 512)
		i++;
	if (!(fixed = ft_strnew(i + 8)))
		return (-1);
	fixed = ft_strcpy(fixed, input);
	fixed[len] = 127;
	fixed = append_len(fixed, i, 4294967296 % len);
	ft_print_n(fixed, i + 8);
	split_input_512(input, i + 8);
}

int				md5(char *input, size_t len, t_words *words)
{
	int i;

	if (padding(input, len, g) == -1)
		return (-1);
	while (g->offset < g->adj_len)
	{
		words->w = (g->msg + g->offset);
		words->a = words->a0;
		words->b = words->b0;
		words->c = words->c0;
		words->d = words->d0;
		i = -1;
		while (++i < 64)
			hashing_functions(words, i);
		words->a0 += words->a;
		words->b0 += words->b;
		words->c0 += words->c;
		words->d0 += words->d;
		words->offset += 64;
	}
	free(words->msg);
	return (0);
