/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:39:49 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/08 23:08:11 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** issue with hash but it still functions without faults. check w
*/

#include "ft_ssl_md5.h"

void	print_sha512(t_512_words *words)
{
	ft_printf("%016lx%016lx%016lx%016lx%016lx%016lx%016lx%016lx", words->h0,
			words->h1, words->h2, words->h3, words->h4, words->h5, words->h6,
			words->h7);
}

void	split_padded_1024(char *fixed, int len, t_512_words *words)
{
	char			*chunk;
	int				i;

	i = 0;
	while (i < len)
	{
		chunk = ft_strnew(128);
		ft_memcpy(chunk, fixed + i, 128);
		process_chunk_512(chunk, words);
		free(chunk);
		i += 128;
	}
}

char	*flip_512(unsigned long *padded, int len)
{
	int				j;

	j = -1;
	while (++j < ((len) / 4))
		padded[j] = flip_end_512(padded[j]);
	return ((char *)padded);
}

int		sha_pad_512(char *input, unsigned len, t_512_words *words)
{
	int				i;
	unsigned		flen;
	char			*padded;

	i = 1;
	while ((len + i + 8) % 128)
		i++;
	if (!(padded = ft_strnew(i + len + 8)))
		return (-1);
	padded = ft_memcpy(padded, input, ft_strlen(input));
	padded[len] = (unsigned char)128;
	flen = (len * 8);
	padded = flip_512((unsigned long *)padded, len + i);
	ft_memcpy(padded + len + i + 4, &flen, 4);
	split_padded_1024(padded, len + i + 8, words);
	return (0);
}

int		ft_sha512(char *input)
{
	t_512_words		*words;

	words = (t_512_words *)malloc(sizeof(t_512_words));
	words->h0 = 0x6a09e667f3bcc908;
	words->h1 = 0xbb67ae8584caa73b;
	words->h2 = 0x3c6ef372fe94f82b;
	words->h3 = 0xa54ff53a5f1d36f1;
	words->h4 = 0x510e527fade682d1;
	words->h5 = 0x9b05688c2b3e6c1f;
	words->h6 = 0x1f83d9abfb41bd6b;
	words->h7 = 0x5be0cd19137e2179;
	if (sha_pad_512(input, (unsigned)ft_strlen(input), words) < 0)
	{
		free(words);
		return (-1);
	}
	print_sha512(words);
	free(words);
	return (0);
}
