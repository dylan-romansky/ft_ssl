/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_missing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:23:32 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 17:20:20 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

/* easy lazy way is with getpass */

int		cipher_stdin(t_ssl_input *input)
{
	fcntl(0, F_SETFL, O_NONBLOCK);
	input_file(input, NULL, NULL, 0);
	if (!input->len)
		fcntl(0, F_SETFL, 1);
	return (input->len);
}

void	get_hex_key(t_ssl_input *input, int dis)
{
	char	*tmp;

	tmp = getpass("enter des key in hex: ");
	input->key = check_key(tmp, dis);
}

void	get_iv(t_ssl_input *input, int dis)
{
	char	*tmp;

	tmp = getpass("create initial vector: ");
	input->iv = verify_iv(tmp, dis);
}

void	get_input_file(t_ssl_input *input)
{
	if (!cipher_stdin(input))
		input_file(input, NULL, NULL, 0);
}

void	get_missing(t_ssl_input *input, int dis)
{
	if (!(input->flags & k))
		get_hex_key(input, dis);
	if (input->flags & p2 && !input->pass)
		pass_input(input);
	if ((dis == 6 || dis == 7) && !input->iv)
		get_iv(input, dis);
	if (!(input->flags & i))
		get_input_file(input);
	if (input->len % 8)
		des_len_error(dis);
}
