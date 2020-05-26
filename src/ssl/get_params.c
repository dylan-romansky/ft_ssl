/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 01:07:59 by dromansk          #+#    #+#             */
/*   Updated: 2019/12/03 17:24:04 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					input_file(t_ssl_input *input, char *name, char *fun,
		int fd)
{
//	char	red[BUFF_SIZE + 1];
//	int		len;
//	int		ret;

//	len = 0;
	if (fd == -1)
		no_file(name, fun);
	input->infd = fd;
//	while ((ret = read(fd, red, BUFF_SIZE)) > 0)
//	{
//		red[ret] = '\0';
//		input->input = ft_hardjoin(input->input, len, red, ret);
//		len += ret;
//	}
//	if (ret < 0 && fd != 0)
//	{
//		free(input->input);
//		no_read(name, fun);
//	}
//	input->len = len;
	return (1);
}

int					output_file(t_ssl_input *input, char *path)
{
	input->outfd = open(path, O_RDWR | O_CREAT, 0644);
	return (1);
}

unsigned			hex_val(char in)
{
	if ('a' <= in && in <= 'f')
		return (in - 'a' + 10);
	if ('A' <= in && in <= 'F')
		return (in - 'A' + 10);
	return (in - '0');
}

unsigned long long	hex_to_l(char *st)
{
	unsigned long long	hex;

	hex = 0;
	while (('a' <= *st && *st <= 'f') || ('A' <= *st && *st <= 'F') ||
			('0' <= *st && *st <= '9'))
	{
		hex *= 16;
		hex += hex_val(*st);
		st++;
	}
	while (!(hex & 0xff00000000000000L))
		hex <<= 8;
	return (hex);
}

int					get_pass(t_ssl_input *input, char *pass)
{
	input->pass = pass;
	return (2);
}
