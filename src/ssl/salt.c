/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   salt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:23:13 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 21:09:15 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	salt_error(int dis)
{
	if (dis == 6)
		ft_printf("des: Error: invalid hex salt input.\n");
	if (dis == 7)
		ft_printf("des-cbc: Error: invalid hex salt input.\n");
	if (dis == 8)
		ft_printf("des-ecb: Error: invalid hex salt input.\n");
	exit(1);
}

unsigned long	verify_salt(char *tmp, int dis)
{
	int				i;
	char			*key;
	unsigned long	done;

	i = -1;
	key = (ft_strlen(tmp) <= 16) ? ft_strdup(tmp) : ft_strndup(tmp, 16);
	while (key[++i])
		if (!(('a' <= key[i] && key[i] <= 'f') || ('A' <= key[i] &&
						key[i] <= 'F') || ('0' <= key[i] && key[i] <= '9')))
			salt_error(dis);
	done = hex_to_l(key);
	free(key);
	return (done);
}

unsigned long	gen_salt(void)
{
	unsigned long	salt;

	getentropy(&salt, 8);
	return (salt);
}
