/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:34:09 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/24 18:22:35 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const unsigned long g_k3[] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

unsigned long	rightrotate64(unsigned long input, unsigned long amount)
{
	return ((((unsigned long)input >> amount)) | (input << (64 - amount)));
}

void			add_512_hash(t_512_words *words)
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

void			hash_512(t_512_words *words, unsigned long *w, int i)
{
	words->tmp1 = rightrotate64(words->e, 14) ^ rightrotate64(words->e, 18) ^
		rightrotate64(words->e, 41);
	words->tmp2 = (words->e & words->f) ^ (~words->e & words->g);
	words->tmp3 = words->h + words->tmp1 + words->tmp2 + g_k3[i] + w[i];
	words->tmp4 = rightrotate64(words->a, 28) ^ rightrotate64(words->a, 34) ^
		rightrotate64(words->a, 39);
	words->tmp5 = (words->a & words->b) ^ (words->a & words->c) ^
		(words->b & words->c);
	words->tmp6 = words->tmp4 + words->tmp5;
	words->h = words->g;
	words->g = words->f;
	words->f = words->e;
	words->e = words->d + words->tmp3;
	words->d = words->c;
	words->c = words->b;
	words->b = words->a;
	words->a = words->tmp3 + words->tmp6;
}

void			hashing_function_512(t_512_words *words, unsigned long *w)
{
	int	i;

	i = -1;
	while (++i < 80)
		hash_512(words, w, i);
	add_512_hash(words);
}

void			process_chunk_512(char *chunk, t_512_words *words)
{
	unsigned long	*w;
	unsigned long	tmp1;
	unsigned long	tmp2;
	int				i;

	i = 15;
	w = (unsigned long *)ft_strnew(sizeof(unsigned long) * 80);
	ft_memcpy(w, chunk, 16 * 8);
	while (++i < 80)
	{
		tmp1 = rightrotate64(w[i - 15], 1) ^ rightrotate64(w[i - 15], 8) ^
			(w[i - 15] >> 7);
		tmp2 = rightrotate64(w[i - 2], 19) ^ rightrotate64(w[i - 2], 61) ^
			(w[i - 2] >> 6);
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
	hashing_function_512(words, w);
}
