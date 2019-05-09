/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 01:07:59 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 01:37:54 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					input_file(t_ssl_input *input, char *path)
{
	input->infd = open(path, O_RDONLY);
	return (2);
}

int					output_file(t_ssl_input *input, char *path)
{
	input->outfd = open(path, O_RDWR);
	return (2);
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
	}
	return (hex);
}

int					get_pass(t_ssl_input *input, char *pass)
{
	input->pass = pass;
	return (2);
}
