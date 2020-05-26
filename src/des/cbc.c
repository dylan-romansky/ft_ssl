/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:53:09 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/13 07:28:02 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void	ft_des_cbc_e(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	vector; //swap this out for input->iv
	unsigned long	subkeys[16];
	size_t			i;

	i = 0;
	gen_key(input->key, subkeys);
	vector = input->iv;
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = flip_end_512(chunk);
		chunk ^= vector;
		chunk = init_perm(chunk);
		chunk = flip_end_512(split_perm_e(chunk, subkeys));
		ft_memcpy(input->input + i, &chunk, 8);
		vector = flip_end_512(chunk);
		i += 8;
	}
	if (input->flags & a)
	{
		input->read = input->len;
		ft_base64_e(input);
	}
}

void	ft_des_cbc_d(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	vector;
	unsigned long	subkeys[16];
	size_t			i;

	i = 0;
	gen_key(input->key, subkeys);
	while (i < input->len)
	{
		vector = input->iv;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = flip_end_512(chunk);
		input->iv = chunk;
		chunk = init_perm(chunk);
		chunk = split_perm_d(chunk, subkeys);
		chunk = flip_end_512(chunk ^ vector);
		ft_memcpy(input->input + i, &chunk, 8);
		i += 8;
	}
}
