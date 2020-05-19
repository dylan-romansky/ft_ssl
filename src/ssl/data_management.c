/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:22:55 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/31 02:46:34 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			key_error(int dis)
{
	if (dis == 6)
		ft_printf("des: error: invalid hex key input.\n");
	else if (dis == 7)
		ft_printf("des-cbc: error: invalid hex key input.\n");
	else if (dis == 8)
		ft_printf("des-ecb: error: invalid hex key input.\n");
	exit(1);
}

unsigned long	check_key(char *k, int dis)
{
	int				i;
	char			key[17];
	unsigned long	done;

	i = ft_strlen(k);
	ft_bzero(key, 17);
	ft_memcpy(key, k, i <= 16 ? i : 16);
	i = -1;
	while (key[++i])
		if (!(('a' <= key[i] && key[i] <= 'f') || ('A' <= key[i] &&
						key[i] <= 'F') || ('0' <= key[i] && key[i] <= '9')))
			key_error(dis);
	while (i < 16)
		key[i++] = '0';
	done = hex_to_l(key);
	ft_bzero(key, 17);
	return (done);
}

void			iv_error(int dis)
{
	if (dis == 6)
		ft_printf("des: Error: invalid hex iv input.\n");
	else if (dis == 7)
		ft_printf("des-cbc: Error: invalid hex iv input.\n");
	else if (dis == 8)
		ft_printf("des-ecb: Error: invalid hex iv input.\n");
	exit(1);
}

unsigned long	verify_iv(char *k, int dis)
{
	int				i;
	char			key[17];
	unsigned long	done;

	ft_bzero(key, 17);
	i = ft_strlen(k);
	ft_memcpy(key, k, i <= 16 ? i : 16);
	if (i < 16)
		pad_iv(key);
	i = -1;
	while (key[++i])
		if (!(('a' <= key[i] && key[i] <= 'f') || ('A' <= key[i] &&
						key[i] <= 'F') || ('0' <= key[i] && key[i] <= '9')))
			iv_error(dis);
	done = hex_to_l(key);
	ft_bzero(key, 17);
	return (done);
}
