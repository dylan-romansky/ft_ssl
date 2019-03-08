/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:39:49 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/07 19:21:33 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** issue with hash but it still functions without faults. check w
*/

#include "ft_ssl_md5.h"

void	print_sha256(t_sha_words *words)
{
	ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x", words->h0, words->h1, 
	words->h2, words->h3, words->h4, words->h5, words->h6, words->h7);
}

void	process_chunk(char *chunk, t_sha_words *words)
{
	unsigned		*w;
	uint32_t		tmp1;
	uint32_t		tmp2;
	int				i;

	i = 15;
	w = (unsigned *)malloc(sizeof(unsigned) * 64);
	ft_memcpy(w, chunk, 16 * 4);
	while (++i < 64)
	{
		tmp1 = rightrotate(w[i - 15], 7) ^ rightrotate(w[i - 15], 18) ^
			(w[i-15] >> 3);
		tmp2 = rightrotate(w[i - 2], 17) ^ rightrotate(w[i - 2], 19) ^
			(w[i - 2] >> 10);
		w[i] = w[i - 16] + tmp1 + w[i - 7] + tmp2;
	}
	words->a = words->h0;
	words->b = words->h1;
	words->c = words->h2;
	words->d = words->h3;
	words->e = words->h4;
	words->f = words->h5;
	words->g = words->h6;
	words->h = words->h7;
	hashing_function_sha(words, w);
}

void	split_padded_512(char *fixed, int len, t_sha_words *words)
{
	char			*chunk;
	int				i;

	i = 0;
	while (i < len)
	{
		chunk = ft_strnew(64);
		ft_memcpy(chunk, fixed, 64);
		process_chunk(chunk, words);
		free(chunk);
		i += 64;
	}
	print_sha256(words);
}

int		sha_pad(char *input, unsigned len, t_sha_words *words)
{
	int				i;
	unsigned		j;
	unsigned long	flen;
	char			*padded;

	i = 0;
	while ((len + i + 8) % 64)
		i++;
	if (!(padded = ft_strnew(i + len + 8)))
		return (-1);
	padded = ft_memcpy(padded, input, ft_strlen(input));
	padded[len] = (unsigned char)128;
	flen = (len * 8);
	j = 0;
	while (j < (len + i - 1))
		flip_end(padded[j++]);//issue here, verify how this needs to flip
	ft_memcpy(padded + len + i, &flen, 8);
	split_padded_512(padded, len + i + 8, words);
	return (0);
}

int		ft_sha256(char *input)
{
	t_sha_words		*words;

	words = (t_sha_words *)malloc(sizeof(t_sha_words));
	words->h0 = 0x6a09e667;
	words->h1 = 0xbb67ae85;
	words->h2 = 0x3c6ef372;
	words->h3 = 0xa54ff53a;
	words->h4 = 0x510e527f;
	words->h5 = 0x9b05688c;
	words->h6 = 0x1f83d9ab;
	words->h7 = 0x5be0cd19;
	if (sha_pad(input, (unsigned)ft_strlen(input), words) < 0)
		return (-1);
	return (0);
}
