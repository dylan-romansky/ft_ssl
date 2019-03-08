/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:29:52 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/07 19:17:07 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

/*
** will need to verify if this works with binary files
*/

void			print_md5(t_md5_words *words)
{
	words->a0 = flip_end(words->a0);
	words->b0 = flip_end(words->b0);
	words->c0 = flip_end(words->c0);
	words->d0 = flip_end(words->d0);
	ft_printf("%08x%08x%08x%08x", words->a0, words->b0, words->c0, words->d0);
	free(words);
}

void			split_input_32(char *chunk, t_md5_words *word)
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
	word->a0 += word->a;
	word->b0 += word->b;
	word->c0 += word->c;
	word->d0 += word->d;
}

void			split_input_512(char *input, int len, t_md5_words *word)
{
	char			*process;
	int				i;
	int				j;

	word->a = word->a0;
	word->b = word->b0;
	word->c = word->c0;
	word->d = word->d0;
	process = ft_strdup(input);
	j = 0;
	while (j < len)
	{
		i = 0;
		process = ft_strnew(64);
		while (i < 64)
			process[i++] = input[j++];
		split_input_32(process, word);
		free(process);
	}
	print_md5(word);
}

int				ft_md5(char *input)
{
	size_t			len;
	int				flen;
	size_t			i;
	char			*fixed;
	t_md5_words		*words;

	words = (t_md5_words *)malloc(sizeof(t_md5_words));
	words->a0 = 0x67452301;
	words->b0 = 0xefcdab89;
	words->c0 = 0x98badcfe;
	words->d0 = 0x10325476;
	len = ft_strlen(input);
	i = len;
	while ((i + 8) % 64)
		i++;
	if (!(fixed = ft_strnew(i + 8)))
		return (-1);
	fixed = ft_memcpy(fixed, input, ft_strlen(input));
	fixed[len] = (unsigned char)128;
	flen = (int)(len * 8);
	ft_memcpy(fixed + i, &flen, 4);
	split_input_512(fixed, i + 8, words);
	free(fixed);
	return (0);
}
