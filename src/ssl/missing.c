/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:23:32 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/12 18:21:21 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

int		cipher_stdin(t_ssl_input *input)
{
	fcntl(0, F_SETFL, O_NONBLOCK);
	input_file(input, NULL, NULL, 0);
	if (!input->len)
		fcntl(0, F_SETFL, 1);
	return (input->len);
}

/*
** void	get_iv(t_ssl_input *input, int dis)
** {
**	char	*tmp;
**
**	tmp = getpass("create initial vector: ");
**	input->iv = verify_iv(tmp, dis);
**}
*/

void	get_key(t_ssl_input *input, int dis)
{
	char *tmp;

	tmp = getpass("enter des key in hex: ");
	input->key = check_key(tmp, dis);
}

void	get_input_file(t_ssl_input *input)
{
	if (!cipher_stdin(input))
		input_file(input, NULL, NULL, 0);
}

void	salt_with_pass(t_ssl_input *input)
{
	if (!input->salt)
		input->salt = gen_salt();
	input->key = salt_pass(input, input->pass, input->salt);
}

void	get_missing(t_ssl_input *input, int dis)
{
	if (dis > 5 && !(input->flags & k) && !(input->flags & d))
	{
		if ((input->flags & p || dis != 8) && !input->pass)
			pass_input(input);
		else if (input->pass)
			salt_with_pass(input);
		else
			get_key(input, dis);
	}
	else if (dis > 5)
	{
		if (input->flags & a)
			debase64_des(input);
		if (!input->salt && ft_strnequ(input->input, "Salted__", 8))
			desalt_des(input);
		else if (!(input->flags & k) && !input->key)
			get_key(input, dis);
	}
	if (!(input->flags & i))
		get_input_file(input);
	if (dis > 5 && input->flags & d && input->len % 8)
		des_len_error(dis);
}
