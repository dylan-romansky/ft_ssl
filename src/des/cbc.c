/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:53:09 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/31 19:22:13 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char	*base64_con_e(unsigned char *s, t_ssl_input *input)
{
	s = (unsigned char *)swap_n_free((char *)ft_base64_e((char *)s,
				input->len), (char **)&s);
	input->len = ft_strlen((char *)s);
	return (s);
}

unsigned char	*base64_con_d(t_ssl_input *input)
{
	int				i;
	unsigned char	*tmp;

	i = input->len;
	input->len = (3 * (input->len / 4)) - minus_pad(input->input);
	tmp = ft_base64_d(input->input, i);
	free(input->input);
	return(tmp);
}

unsigned char	*ft_des_cbc_e(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	vector;
	unsigned long	*subkeys;
	size_t			i;
	unsigned char	*s;

	i = 0;
	subkeys = gen_key(input->key);
	vector = input->iv;
	s = (unsigned char *)ft_strnew(0);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = flip_end_512(chunk);
		chunk ^= vector;
		chunk = init_perm(chunk);
		chunk = flip_end_512(split_perm_e(chunk, subkeys));
		s = (unsigned char *)ft_hardjoin((char *)s, i, (char *)&chunk, 8);
		vector = flip_end_512(chunk);
		i += 8;
	}
	if (input->flags & 256)
		s = base64_con_e(s, input);
	return (s);
}

/*
** fix it, idiot
** it's fucking stupid, the data going into the decryption is identical post
** conversion
** only way there's an issue is if the length is wrong. hmm
*/

unsigned char	*ft_des_cbc_d(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	vector;
	unsigned long	*subkeys;
	size_t			i;
	unsigned char	*s;

	i = 0;
	if (input->flags & 256)
		input->input = (char *)base64_con_d(input);
	subkeys = gen_key(input->key);
	s = (unsigned char *)ft_strnew(0);
	while (i < input->len)
	{
		vector = input->iv;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = flip_end_512(chunk);
		input->iv = chunk;
		chunk = init_perm(chunk);
		chunk = split_perm_d(chunk, subkeys);
		chunk = flip_end_512(chunk ^ vector);
		s = (unsigned char *)ft_hardjoin((char *)s, i, (char *)&chunk, 8);
		i += 8;
	}
	return (s);
}
