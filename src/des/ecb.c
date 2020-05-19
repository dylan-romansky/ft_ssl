/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:53:23 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/13 07:28:10 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void	ft_des_ecb_e(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	subkeys[16];
	size_t			i;
//	unsigned char	*s;

	i = 0;
	gen_key(input->key, subkeys);
//	s = (unsigned char *)ft_strnew(0);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = init_perm(flip_end_512(chunk));
		chunk = flip_end_512(split_perm_e(chunk, subkeys));
	//	s = (unsigned char *)ft_hardjoin((char *)s, i, (char *)&chunk, 8);
		ft_memcpy(input->input + i, &chunk, 8);
		i += 8;
	}
	if (input->flags & a)
	{
		input->read = input->len;
		ft_base64_e(input);
	}
}

void	ft_des_ecb_d(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	subkeys[16];
	size_t			i;
//	unsigned char	*s;

	i = 0;
	gen_key(input->key, subkeys);
//	s = (unsigned char *)ft_strnew(0);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = init_perm(flip_end_512(chunk));
		chunk = flip_end_512(split_perm_d(chunk, subkeys));
//		s = (unsigned char *)ft_hardjoin((char *)s, i, (char *)&chunk, 8);
		ft_memcpy(input->input + i, &chunk, 8);
		i += 8;
	}
//	free(subkeys);
//	return (s);
}
