/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha224.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:49:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/24 18:21:57 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_sha224(void *w)
{
	t_sha_words *words;

	words = (t_sha_words *)w;
	ft_printf("%08x%08x%08x%08x%08x%08x%08x", words->h0, words->h1,
	words->h2, words->h3, words->h4, words->h5, words->h6);
	free(w);
}

void	*ft_sha224(t_ssl_input *input)
{
	t_sha_words		*words;

	words = (t_sha_words *)malloc(sizeof(t_sha_words));
	words->h0 = 0xc1059ed8;
	words->h1 = 0x367cd507;
	words->h2 = 0x3070dd17;
	words->h3 = 0xf70e5939;
	words->h4 = 0xffc00b31;
	words->h5 = 0x68581511;
	words->h6 = 0x64f98fa7;
	words->h7 = 0xbefa4fa4;
/*	if (sha_pad(input->input, (unsigned)(input->len), words) < 0)
	{
		free(words);
		return (-1);
	}*/
	while (read_hash(input, words, &sha_pad))
	{
		flip((unsigned *)input->input, input->read);
		split_padded_512(input->input, input->read, words);
	}
//	print_sha224(words);
	if (input->read == -1)
	{
		free(words);
		words = NULL;
	}
	return (words);
}

/*
 * refer to sha256 ft_sha256.c for reading changes
*/
