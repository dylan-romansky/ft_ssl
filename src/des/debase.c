/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:00:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/11 23:17:53 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	debase64_des(t_ssl_input *input)
{
	input->input = swap_n_free((char *)ft_base64_d(input->input, input->len,
				&(input->input)));
	input->len = (3 * (input->len / 4)) - minus_pad(input->input);
}

void	desalt_des(t_ssl_input *input)	
{
	if (!input->salt && ft_strnequ(input->input, "Salted__", 8))
	{
		ft_memcpy(&(input->salt), input->input + 8, 8);
		ft_pass_key(input);
		input->flags &= s2;
	}
	if (input->flags & s2)
		input->pass ? salt_pass(input, input->pass, input->salt) :
			pass_input(input);
}
