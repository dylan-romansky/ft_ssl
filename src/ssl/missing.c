/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:23:32 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/14 00:43:31 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void	get_key(t_ssl_input *input, int dis)
{
	char *tmp;

	tmp = getpass("enter des key in hex: ");
	input->key = check_key(tmp, dis);
}

void	salt_with_pass(t_ssl_input *input)
{
	if (!input->salt)
		getentropy(&(input->salt), 8);
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
		if (!(input->flags & k) && !input->key)
			get_key(input, dis);
	}
}
