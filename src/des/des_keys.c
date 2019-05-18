/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:04:51 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/17 16:35:18 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** key generation is fucked. check that the left/right handling is good
*/

const int g_keygen56_k[] = {
	57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26,
	18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52,
	44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46,
	38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5,
	28, 20, 12, 4};

const int g_keyshift56_k[] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

const int g_keycat56_k[] = {
	14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19,
	12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37,
	47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34,
	53, 46, 42, 50, 36, 29, 32};

unsigned		key_rotate(unsigned input, unsigned amount)
{
	return ((((unsigned int)input << amount) & 0x0fffffff) |
			(input >> (28 - amount)));
}

unsigned long	gen_cat(unsigned long c, unsigned long d)
{
	unsigned long	k;
	unsigned long	cat;
	int				i;

	k = 0;
	i = -1;
	cat = c << 28;
	cat |= d;
	while (++i < 48)
	{
		k <<= 1;
		k |= ((unsigned long)1 << (56 - g_keycat56_k[i])) & cat ? 1 : 0;
	}
	return (k);
}

/* issue appears to be in this part of the algorithm */

unsigned long	*gen_k(unsigned long c[17], unsigned long d[17])
{
	int				i;
	unsigned long	*k;

	k = (unsigned long *)malloc(sizeof(unsigned long) * 16);
	i = -1;
	while (++i < 16)
	{
		k[i] = gen_cat(c[i + 1], d[i + 1]);
		ft_printf("%56lb\n", k[i]);
	}
	return (k);
}

unsigned long	*gen_key(unsigned long key)
{
	unsigned long	key56;
	int				i;
	unsigned long	c[17];
	unsigned long	d[17];

	key56 = 0;
	i = -1;
	while (++i < 56)
	{
		key56 <<= 1;
		key56 |= ((unsigned long)1 << (64 - g_keygen56_k[i])) & key ? 1 : 0;
	}
	ft_printf("%56lb\n", key56);
	c[0] = (key56 & 0x00fffffff0000000) >> 28;
	d[0] = key56 & 0x0fffffff;
	i = 0;
	while (++i < 17)
	{
		c[i] = key_rotate(c[i - 1], g_keyshift56_k[i - 1]);
		d[i] = key_rotate(d[i - 1], g_keyshift56_k[i - 1]);
	}
	return (gen_k(c, d));
}
