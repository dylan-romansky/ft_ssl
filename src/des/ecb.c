/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:53:23 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/16 21:02:13 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
		chunk = init_perm(chunk);
		chunk = split_perm_e(chunk, subkeys);
		ft_printf("%lX", chunk);
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
		chunk = init_perm(chunk);
		chunk = split_perm_d(chunk, subkeys);
		//write(input->outfd, &chunk, i + 8 <= input->len ? 8 : input->len - i);
		i < input->len - 8 ? ft_printf("%s", &chunk) : ft_printf("%.*s", ((unsigned char *)(&chunk))[7], (char *)&chunk);
		i += 8;
	}
	return (0);
}
