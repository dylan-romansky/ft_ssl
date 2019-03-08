/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:34:09 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/07 23:31:55 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

const uint32_t g_k2[] ={
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

uint32_t	rightrotate(uint32_t input, uint32_t amount)
{
	return ((((unsigned int)input >> amount)) | (input << (32 - amount)));
}

void		add_hash(t_sha_words *words)
{
	words->h0 += words->a;
	words->h1 += words->b;
	words->h2 += words->c;
	words->h3 += words->d;
	words->h4 += words->e;
	words->h5 += words->f;
	words->h6 += words->g;
	words->h7 += words->h;
}

void		hash(t_sha_words *words, unsigned *w, int i)
{
	words->tmp1 = rightrotate(words->e, 6) ^ rightrotate(words->e, 11) ^
		rightrotate(words->e, 25);
	words->tmp2 = (words->e & words->f) ^ (~words->e & words->g);
	words->tmp3 = words->h + words->tmp1 + words->tmp2 + g_k2[i] + w[i];
	words->tmp4 = rightrotate(words->a, 2) ^ rightrotate(words->a, 13) ^
			rightrotate(words->a, 22);
	words->tmp5 = (words->a & words->b) ^ (words->a & words->c) ^
		(words->b & words->c);
	words->h = words->g;
	words->g = words->f;
	words->f = words->e;
	words->e = words->d + words->tmp3;
	words->d = words->c;
	words->c = words->b;
	words->b = words->a;
	words->a = words->tmp3 + words->tmp6;
	add_hash(words);
}

void		hashing_function_sha(t_sha_words *words, unsigned *w)
{
	int	i;

	i = -1;
	while (++i < 64)
		hash(words, w, i);
}

void	sha_process_chunk(char *chunk, t_sha_words *words)
{
	unsigned		*w;
	uint32_t		tmp1;
	uint32_t		tmp2;
	int				i;

	i = 15;
	w = (unsigned *)ft_strnew(sizeof(unsigned) * 64);
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
