/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha384.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:39:49 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/24 18:22:22 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_sha384(void *w)
{
	t_512_words *words;

	words = (t_512_words *)w;
	ft_printf("%016lx%016lx%016lx%016lx%016lx%016lx", words->h0,
			words->h1, words->h2, words->h3, words->h4, words->h5);
	free(w);
}

void	*ft_sha384(t_ssl_input *input)
{
	t_512_words		*words;

	words = (t_512_words *)malloc(sizeof(t_512_words));
	words->h0 = 0xcbbb9d5dc1059ed8;
	words->h1 = 0x629a292a367cd507;
	words->h2 = 0x9159015a3070dd17;
	words->h3 = 0x152fecd8f70e5939;
	words->h4 = 0x67332667ffc00b31;
	words->h5 = 0x8eb44a8768581511;
	words->h6 = 0xdb0c2e0d64f98fa7;
	words->h7 = 0x47b5481dbefa4fa4;
/*	if (sha_pad_512(input->input, (unsigned)(input->len), words) < 0)
	{
		free(words);
		return (-1);
	}*/
	while (read_hash(input, words, &sha_512_pad))
	{
		flip_512((unsigned long *)input->input, input->read);
		split_padded_1024(input->input, input->read, words);
	}
	print_sha384(words);
	if (input->read == -1)
	{
		free(words);
		words = NULL;
	}
	return (0);
}

/*
 * refer to sha256 for reading changes
*/
