/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:23:13 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 19:26:43 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/* research https://github.com/ElliotFriedman/ft_ssl_des/blob/master/md5_salt/md5hash.c */

void			pass_input(t_ssl_input *input)
{
	char			*tmp;
	unsigned long	salt;

	tmp = getpass("enter des encryption password: ");
	salt = gen_salt();
	input->key = salt_pass(tmp, salt);
}
