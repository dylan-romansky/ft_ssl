/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:53:23 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/30 18:11:32 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	get_len(unsigned char *chunk)
{
	int				i;
	int				c;

	i = 7;
	c = chunk[7];
	if (c > 7)
		return (8);
	while (i > (7 - c))
		if (chunk[i--] != c)
			return (8);
	return (8 - chunk[7]);
}

int	ft_des_ecb_e(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	*subkeys;
	size_t			i;

	i = 0;
	subkeys = gen_key(input->key);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = init_perm(flip_end_512(chunk));
		chunk = flip_end_512(split_perm_e(chunk, subkeys));
		write(input->outfd, &chunk, 8);
		i += 8;
	}
	return (0);
}

int	ft_des_ecb_d(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	*subkeys;
	size_t			i;

	i = 0;
	if (input->len % 8)
	{
		ft_printf("Message not multiple of block length");
		exit(1);
	}
	subkeys = gen_key(input->key);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = init_perm(flip_end_512(chunk));
		chunk = flip_end_512(split_perm_d(chunk, subkeys));
		write(input->outfd, &chunk, i + 8 < input->len ? 8 :
				get_len((unsigned char *)&chunk));
		i += 8;
	}
	return (0);
}
