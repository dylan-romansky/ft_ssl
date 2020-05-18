/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:39:49 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/24 18:22:09 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void	print_sha256(void *w)
{
	t_sha_words *words;

	words = (t_sha_words *)w;
	ft_printf("%08x%08x%08x%08x%08x%08x%08x%08x", words->h0, words->h1,
	words->h2, words->h3, words->h4, words->h5, words->h6, words->h7);
	free(w);
}

void	split_padded_512(char *fixed, int len, t_sha_words *words)
{
	char			chunk[64];
	int				i;

	i = 0;
	while (i < len)
	{
		ft_bzero(chunk, 64);
		ft_memcpy(chunk, fixed + i, 64);
		sha_process_chunk(chunk, words);
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
/*
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
	ft_memcpy(padded, input, len);
	padded[len] = (unsigned char)128;
	flen = (len * 8);
	padded = flip((unsigned *)padded, len + i);
	ft_memcpy(padded + len + i + 4, &flen, 4);
	split_padded_512(padded, len + i + 8, words);
	return (0);
}*/

void	sha_pad(t_ssl_input *input, void *words)
{
	size_t 		flen;
	t_sha_words	*w;

	input->len += input->read;
	if (input->read < BUFF_SIZE)
	{
		w = (t_sha_words *)words;
		if (input->read + 1 > BUFF_SIZE - 8)
		{
			flip((unsigned *)input->input, 64);
			split_padded_512(input->input, 64, w);
			input->read -= 64;
			ft_memcpy(input->input, input->input + 64, input->read);
		}
		input->input[input->read++] = (unsigned char)128;
		while ((input->read + 8) % 64)
			input->input[input->read++] = 0;
		flen = input->len * 8;
		flen = flen << 32 | flen >> 32;
		ft_memcpy(input->input + input->read, &flen, 8);
	}
	flip((unsigned *)input->input, input->read);
	if (input->read < BUFF_SIZE)
		input->read += 8;
}

void	*ft_sha256(t_ssl_input *input)
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
	/*if (sha_pad(input->input, (unsigned)(input->len), words) < 0)
	{
		free(words);
		return (-1);
	}*/
	while (read_hash(input, words, &sha_pad) > 0)
		split_padded_512(input->input, input->read, words);
//	print_sha256(words);
	if (input->read == -1)
	{
		free(words);
		words = NULL;
	}
	return (words);
}

/*
 * instead of sha_pad first, read chunks of 64 bytes
 * on last chunk pad up to 64 as usual
*/
