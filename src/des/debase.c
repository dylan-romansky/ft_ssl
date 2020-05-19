/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:00:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/14 00:45:42 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void			debase64_des(t_ssl_input *input)
{
	ft_memcpy(input->base, input->input, input->len);
	while (input->len > 0 && input->len < BUFF_SIZE)
	{
		input->len += input->read;
		strip_nl(input);
		input->read = read(input->infd, input->base + input->len, BUFF_SIZE - input->read);
	}
	ft_base64_d(input);
	ft_bzero(input->base, BUFF_SIZE / 3 * 4);
}
//a lot has changed about the salt for this so verify behaviour
void			desalt_des(t_ssl_input *input)
{
//	char	*tmp;

	ft_memcpy(&(input->salt), input->input + 8, 8);
//	tmp = ft_strsub(input->input, 16, input->len - 16);
//	free(input->input);
//	input->input = tmp;
	input->len -= 16;
	input->flags |= s2;
	pass_input(input);
}
/*
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
}*/
