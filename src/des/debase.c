/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:00:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/13 03:56:37 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void			debase64_des(t_ssl_input *input)
{
	int	new_len;

	new_len = (3 * (input->len / 4)) - minus_pad(input->input);
	input->input = swap_n_free((char *)ft_base64_d(input->input, input->len),
				&(input->input));
	input->len = new_len;
}

void			desalt_des(t_ssl_input *input)	
{
	char	*tmp;

	ft_memcpy(&(input->salt), input->input + 8, 8);
	tmp = ft_strsub(input->input, 16, input->len - 16);
	free(input->input);
	input->input = tmp;
	input->len -= 16;
	input->flags |= s2;
	pass_input(input);
}

unsigned char	*append_salt(unsigned char *s, t_ssl_input *input)
{
	char *new;

	new = ft_strnew(16);
	ft_memcpy(new, "Salted__", 8);
	ft_memcpy(new + 8, &(input->salt), 8);
	new = ft_hardjoin(new, 16, (char *)s, input->len);
	input->len += 16;
	free(s);
	return ((unsigned char *)new);
}
