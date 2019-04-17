/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha224.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:49:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/16 20:16:04 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	print_sha224(t_sha_words *words)
{
	ft_printf("%08x%08x%08x%08x%08x%08x%08x", words->h0, words->h1,
	words->h2, words->h3, words->h4, words->h5, words->h6);
}

int		ft_sha224(t_ssl_input *input)
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
	if (sha_pad(input->input, (unsigned)(input->len), words) < 0)
	{
		free(words);
		return (-1);
	}
	print_sha224(words);
	free(words);
	return (0);
}
