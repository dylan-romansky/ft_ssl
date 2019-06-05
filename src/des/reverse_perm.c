/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_perm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:05:33 by dromansk          #+#    #+#             */
/*   Updated: 2019/06/04 17:40:20 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const int	g_rev_perm_k[] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47,
	15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22,
	62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36,
	4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11,
	51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58,
	26, 33, 1, 41, 9, 49, 17, 57, 25};

unsigned long	reverse_permute(unsigned left, unsigned right)
{
	unsigned long	rev;
	unsigned long	perm;
	int				i;

	rev = ((unsigned long)right << 32) | left;
	i = -1;
	perm = 0;
	while (++i < 64)
	{
		perm <<= 1;
		perm |= ((unsigned long)1 << (64 - g_rev_perm_k[i])) & rev ? 1 : 0;
	}
	return (perm);
}

unsigned long	split_perm_e(unsigned long perm, unsigned long *key48)
{
	unsigned		left[17];
	unsigned		right[17];
	int				i;

	left[0] = perm >> 32;
	right[0] = perm & 0xffffffff;
	i = 0;
	while (++i < 17)
	{
		left[i] = right[i - 1];
		right[i] = left[i - 1] ^ key_encrypt(right[i - 1], key48[i - 1]);
	}
	return (reverse_permute(left[16], right[16]));
}

unsigned long	split_perm_d(unsigned long perm, unsigned long *key48)
{
	unsigned		left[17];
	unsigned		right[17];
	int				i;

	left[0] = perm >> 32;
	right[0] = perm & 0xffffffff;
	i = 0;
	while (++i < 17)
	{
		left[i] = right[i - 1];
		right[i] = left[i - 1] ^ key_encrypt(right[i - 1], key48[16 - i]);
	}
	return (reverse_permute(left[16], right[16]));
}
