/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 01:55:56 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/06 16:39:12 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

const uint32_t g_rot[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12,
	17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21};

const uint32_t g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

uint32_t	leftrotate(uint32_t bits, uint32_t rot)
{
	return (((bits) << (rot)) | ((bits) >> (32 - (rot))));
}

void		hashing_functions_md5(t_words *words, int i, unsigned *chunks)
{
	int		g;

	g = 0;
	if (i < 16)
	{
		words->f = (words->b & words->c) | (~words->b & words->d);
		g = i;
	}
	else if (i < 32)
	{
		words->f = (words->b & words->d) | (words->c & ~words->d);
		g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		words->f = words->b ^ words->c ^ words->d;
		g = (3 * i + 5) % 16;
	}
	else
	{
		words->f = words->c ^ (words->b | ~words->d);
		g = (7 * i) % 16;
	}
	words->f = words->f + words->a + g_k[i] + chunks[g];
	words->a = words->d;
	words->d = words->c;
	words->c = words->b;
	words->b = words->b + leftrotate(words->f, g_rot[i]);
}

unsigned	flip_end(unsigned num)
{
	unsigned	bit;
	unsigned	flipped;

	bit = 1;
	flipped = 0;
	while (num)
	{
		flipped <<= 1;
		if (bit & num)
			flipped += 1;
		num >>= 1;
	}
	return (flipped);
}
