/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:29:52 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/22 17:00:35 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void	read_stdin(t_ssl_input *input)
{
	int	old;

	if (input->read == 0)
	{
		old = fcntl(STDIN_FILENO, F_GETFL);
		fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
		input->read = read(input->infd, input->input, BUFF_SIZE);
		fcntl(STDIN_FILENO, F_SETFL, old);
		if (input->read < 0 && input->flags & nof)
			input->read = read(input->infd, input->input, BUFF_SIZE);
	}
	else
		input->read = read(input->infd, input->input, BUFF_SIZE);
}

void	read_string(t_ssl_input *input)
{
	size_t len;

	len = ft_strlen(input->sflag);
	if (*(input->sflag))
	{
		input->read = len < BUFF_SIZE ? len : BUFF_SIZE;
		ft_memcpy(input->input, input->sflag, input->read);
		input->sflag += input->read;
	}
}

int		read_hash(t_ssl_input *input, void *w, void (*pad)(t_ssl_input *, void *))
{
	ft_bzero(input->input, BUFF_SIZE);
	input->read = 0;
	if (input->flags & s)
		read_string(input);
	else if (input->infd == STDIN_FILENO)
		read_stdin(input);
	else
		input->read = read(input->infd, input->input, BUFF_SIZE);
	if (!(input->flags & readed) && input->read <= 0)
		input->read = -1;
	if (input->read <= 0)
		return (input->read);
	input->flags |= readed;
	if ((input->flags & (p | s)) == p && input->infd == STDIN_FILENO)
		write(input->outfd, input->input, input->read);
	pad(input, w);
	return (1);
}

int		read_cipher(t_ssl_input *input, void (*pad)(t_ssl_input *))
{
	if (input->infd == STDIN_FILENO)
		read_stdin(input);
	else
		input->read = read(input->infd, input->input, BUFF_SIZE);
	if (!(input->flags & readed) && input->read <= 0)
		input->read = -1;
	if (input->read <= 0)
		return (input->read);
	input->flags |= readed;
	input->len += input->read;
	if (pad)
		pad(input);
	return (1);
}
