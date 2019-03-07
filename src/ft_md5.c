/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:29:52 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/06 16:05:34 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void			print_hash(t_words *word)
{
	words->a0 = flip_end(words->a0);
	words->b0 = flip_end(words->b0);
	words->c0 = flip_end(words->c0);
	words->d0 = flip_end(words->d0);
	ft_printf("%x%x%x%x\n", words->a0, words->b0, words->c0, words->d0);
	//might end up backwords, will need to check
	free(word);
}

int				hash_md5(char *input, size_t len, t_words *words)
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
	return (0);
}

void			split_input_32(char *chunk, t_words *word)
{
	unsigned		words[16];
	int				i;
	int				j;
	int				num;

	i = 0;
	j = 0;
	while (j < 64)
	{
		memcpy(&num, chunk + j, 4);
		words[i++] = num;
		j += 4;
	}
	i = -1;
	while (++i < 64)
		hashing_functions_md5(word, i, words);
	words->a0 += words->a;
	words->b0 += words->b;
	words->c0 += words->c;
	words->d0 += words->d;
}

void			split_input_512(char *input, int len, t_words *word)
{
	char			*process;
	int				i;
	int				j;

	words->a = words->a0;
	words->b = words->b0;
	words->c = words->c0;
	words->d = words->d0;
	process = ft_strdup(input);
	j = -1;
	while (j < len)
	{
		i = -1;
		process = ft_strnew(64);
		while (input[++j] && ++i < 64)
			process[i] = input[j];
		split_input_32(process, word);
		free(process);
	}
	print_hash(word);
}

int				padding(char *input)
{
	size_t			len;
	size_t			flen;
	size_t			i;
	char			*fixed;
	t_words			*words;

	words = (t_words *)malloc(sizeof(t_words));
	words->a0 = 0x67452301;
	words->b0 = 0xefcdab89;
	words->c0 = 0x98badcfe;
	words->d0 = 0x10325476;
	words->offset = 0;
	len = ft_strlen(input);
	i = len;
	while ((i + 8) % 64 || (i + 8) < 64)
		i++;
	if (!(fixed = ft_strnew(i + 8)))
		return (-1);
	fixed = ft_memcpy(fixed, input, ft_strlen(input));
	fixed[len] = 128; //potential problem area, confirm this works
	flen = len * 8;
	ft_memcpy(fixed + i + 1, &flen, 4);
	split_input_512(input, i + 8, words);
	free(fixed);
	return (0);
}
