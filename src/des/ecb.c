/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:53:23 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 15:07:23 by dromansk         ###   ########.fr       */
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
		ft_dprintf(input->outfd, "%16llX", chunk);
		i += 8;
	}
	return (0);
}
/* check message length and print error if it's wrong length for decoding */
/* "Message not multiple of block length" */
int	ft_des_ecb_d(t_ssl_input *input)
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
		chunk = split_perm_d(chunk, subkeys);
		write(input->outfd, &chunk, i + 8 <= input->len ? 8 : input->len - i);
		i += 8;
	}
	return (0);
}
