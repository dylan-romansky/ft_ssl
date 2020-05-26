/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   salt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:23:13 by dromansk          #+#    #+#             */
/*   Updated: 2019/12/03 17:27:32 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** salted output uses a header that reads "Salted__" + 8 byte salt
** --only when -p flag present, otherwise it just gets appended
*/

void			salt_error(int dis)
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
	char			key[17];
	unsigned long	done;

	i = ft_strlen(tmp);
	ft_bzero(key, 17);
	ft_memcpy(key, tmp, i <= 16 ? i : 16);
	i = -1;
	while (key[++i])
		if (!(('a' <= key[i] && key[i] <= 'f') || ('A' <= key[i] &&
						key[i] <= 'F') || ('0' <= key[i] && key[i] <= '9')))
			salt_error(dis);
	done = flip_end_512(hex_to_l(key));
	ft_bzero(key, 17);
	return (done);
}
