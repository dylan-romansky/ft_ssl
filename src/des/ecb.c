/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:53:23 by dromansk          #+#    #+#             */
/*   Updated: 2019/06/04 17:52:30 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	*ft_des_ecb_e(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	*subkeys;
	size_t			i;
	unsigned char	*s;

	i = 0;
	subkeys = gen_key(input->key);
	s = (unsigned char *)ft_strnew(0);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = init_perm(flip_end_512(chunk));
		chunk = flip_end_512(split_perm_e(chunk, subkeys));
		s = (unsigned char *)ft_hardjoin((char *)s, i, (char *)&chunk, 8);
		i += 8;
	}
	if (input->flags & 256)
	{
		s = (unsigned char *)swap_n_free((char *)ft_base64_e((char *)s,
					input->len), (char **)&s);
		input->len = ft_strlen((char *)s);
	}
	free(subkeys);
	return (s);
}

/*
** problem exists in base64 decryption
** narrow down whether it's the algorithm itself or the assignment process
*/

unsigned char	*ft_des_ecb_d(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	*subkeys;
	size_t			i;
	unsigned char	*s;

	if (input->flags & 256)
	{
		input->input = swap_n_free((char *)ft_base64_d(input->input,
					input->len), &(input->input));
		input->len = (3 * (input->len / 4)) - minus_pad(input->input);
	}
	i = 0;
	while (i < input->len)
		print_bin(input->input[i++], 8);
	i = 0;
	subkeys = gen_key(input->key);
	s = (unsigned char *)ft_strnew(0);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = init_perm(flip_end_512(chunk));
		chunk = flip_end_512(split_perm_d(chunk, subkeys));
		s = (unsigned char *)ft_hardjoin((char *)s, i, (char *)&chunk, 8);
		i += 8;
	}
	free(subkeys);
	return (s);
}
