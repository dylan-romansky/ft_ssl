/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:39:49 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/12 19:22:25 by dromansk         ###   ########.fr       */
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

void	split_padded_512(char *fixed, int len, t_sha_words *words)
{
	char			*chunk;
	int				i;

	i = 0;
	while (i < len)
	{
		chunk = ft_strnew(64);
		ft_memcpy(chunk, fixed + i, 64);
		sha_process_chunk(chunk, words);
		free(chunk);
		i += 64;
	}
}

char	*flip(unsigned *padded, int len)
{
	int				j;

	j = -1;
	while (++j < ((len) / 4))
		padded[j] = flip_end(padded[j]);
	return ((char *)padded);
}

int		sha_pad(char *input, unsigned len, t_sha_words *words)
{
	int				i;
	unsigned		flen;
	char			*padded;

	i = 1;
	while ((len + i + 8) % 64)
		i++;
	if (!(padded = ft_strnew(i + len + 8)))
		return (-1);
	padded = ft_memcpy(padded, input, len);
	padded[len] = (unsigned char)128;
	flen = (len * 8);
	padded = flip((unsigned *)padded, len + i);
	ft_memcpy(padded + len + i + 4, &flen, 4);
	split_padded_512(padded, len + i + 8, words);
	return (0);
}

int		ft_sha256(char *input, size_t len)
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
	if (sha_pad(input, (unsigned)len, words) < 0)
	{
		free(words);
		return (-1);
	}
	print_sha256(words);
	free(words);
	return (0);
}
