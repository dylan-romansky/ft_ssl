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
	unsigned int	val;
	unsigned		i;

	if (input->len < BUFF_SIZE && !(input->flags & d))
	{
		i = 0;
		val = 8 - (input->len % 8);
		while (i < val)
			input->input[i++ + input->read] = val;
		input->len += val;
	}
}

void			put_salt(t_ssl_input *input)
{
	unsigned char	*salt;
	int				i;

	salt = (unsigned char *)&input->salt;
	i = -1;
	while (++i < 8)
		salt[i] = salt[i] << 4 | salt[i] >> 4;
	write(input->outfd, &input->salt, 8);
}

void			des_salt_handling(t_ssl_input *input)
{
	if (!(input->flags & d))
	{
		if (input->flags & s2)
			write(input->outfd, "Salted__", 8);
		if (input->salt)//double check when salt gets added
			put_salt(input);
	}
	else
	{
		read(input->infd, input->input, 8);
		if (ft_strncmp(input->input, "Salted__", 8))
			read(input->infd, input->input, 8);
		if (!input->salt)//verify openssl with salt flag and no salt provided
			ft_memcpy(&input->salt, input->input, 8);
	}
	ft_bzero(input->input, 8);
}

void			*ft_des_ecb(t_ssl_input *input)
{
	if (input->salt || input->flags & s2)
		des_salt_handling(input);
	while (read_cipher(input, &des_pad) > 0)
	{
		if (input->flags & d)
		{
			if (input->flags & a)
				debase64_des(input);
			if (input->len % 8)
				blocksize_error();
			ft_des_ecb_d(input);
			write(input->outfd, input->input, get_len(input->input, input->len));
		}
		else
		{
			ft_des_ecb_e(input);
			input->flags & a ? print_base64((char *)input->base, input->outfd, input->len) :
				write(input->outfd, input->input, input->len);
		}
	}
	return (0);
}

void			*ft_des_cbc(t_ssl_input *input)
{
	if (input->salt || input->flags & s2)
		des_salt_handling(input);
	while (read_cipher(input, &des_pad) > 0)
	{
		if (input->flags & d)
		{
			if (input->flags & a)
				debase64_des(input);
			if (input->len % 8)
				blocksize_error();
			ft_des_cbc_d(input);
			write(input->outfd, input->input, get_len(input->input, input->len));
		}
		else
		{
			ft_des_cbc_e(input);
			input->flags & a ? print_base64((char *)input->base, input->outfd, input->len) :
				write(input->outfd, input->input, input->len);
		}
	}
	return (0);
}
