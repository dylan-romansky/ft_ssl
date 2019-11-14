/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:57:14 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/14 00:59:58 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void			blocksize_error(void)
{
	ft_printf("Message not multiple of block length\n");
	exit(1);
}

int				get_len(char *s, int len)
{
	int				i;
	int				c;

	i = 0;
	c = s[len - 1];
	if (c > 8 || c < 0)
		return (len);
	while (i < c)
		if (s[len - ++i] != c)
			return (len);
	return (len - i);
}

void			des_pad(t_ssl_input *input)
{
	unsigned char	*pad;
	unsigned int	val;
	unsigned		i;

	i = 0;
	val = 8 - (input->len % 8);
	pad = (unsigned char *)ft_strnew(input->len + val);
	ft_memcpy(pad, input->input, input->len);
	while (i < val)
		pad[i++ + input->len] = val;
	free((input->input));
	input->input = (char *)pad;
	input->len += val;
}

int				ft_des_ecb(t_ssl_input *input)
{
	unsigned char	*s;

	s = NULL;
	if (!(input->flags & d))
		des_pad(input);
	if (input->flags & d)
	{
		s = ft_des_ecb_d(input);
		write(input->outfd, s, get_len((char *)s, input->len));
	}
	else
	{
		s = ft_des_ecb_e(input);
		input->flags & a ? print_base64((char *)s, input->outfd, input->len) :
			write(input->outfd, s, input->len);
	}
	free(s);
	return (0);
}

int				ft_des_cbc(t_ssl_input *input)
{
	unsigned char	*s;

	s = NULL;
	if (!(input->flags & d))
		des_pad(input);
	if (input->flags & d)
	{
		s = ft_des_cbc_d(input);
		write(input->outfd, s, get_len((char *)s, input->len));
	}
	else
	{
		s = ft_des_cbc_e(input);
		input->flags & a ? print_base64((char *)s, input->outfd, input->len) :
			write(input->outfd, s, input->len);
	}
	free(s);
	return (0);
}
