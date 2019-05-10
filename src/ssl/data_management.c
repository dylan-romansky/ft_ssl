/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 16:22:55 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/10 13:35:41 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			key_error(int dis)
{
	if (dis == 6)
		ft_printf("des: error: invalid hex key input.\n");
	if (dis == 7)
		ft_printf("des-cbc: error: invalid hex key input.\n");
	if (dis == 8)
		ft_printf("des-ecb: error: invalid hex key input.\n");
	exit(1);
}

unsigned long	check_key(char *k, int dis)
{
	int				i;
	char			*key;
	unsigned long	done;

	i = -1;
	key = (ft_strlen(k) <= 16) ? ft_strdup(k) : ft_strndup(k, 16);
	while (key[++i])
		if (!(('a' <= key[i] && key[i] <= 'f') || ('A' <= key[i] &&
						key[i] <= 'F') || ('0' <= key[i] && key[i] <= '9')))
			key_error(dis);
	while (ft_strlen(key) < 16)
		key = ft_hardjoin(key, ft_strlen(key), "0", 1);
	done = hex_to_l(key);
	free(key);
	return (done);
}

void			iv_error(int dis)
{
	if (dis == 6)
		ft_printf("des: Error: invalid hex iv input.\n");
	if (dis == 7)
		ft_printf("des-cbc: Error: invalid hex iv input.\n");
	if (dis == 8)
		ft_printf("des-ecb: Error: invalid hex iv input.\n");
	exit(1);
}

unsigned long	verify_iv(char *tmp, int dis)
{
	int				i;
	char			*key;
	unsigned long	done;

	i = -1;
	key = (ft_strlen(tmp) <= 16) ? pad_iv(tmp) : ft_strndup(tmp, 16);
	while (key[++i])
		if (!(('a' <= key[i] && key[i] <= 'f') || ('A' <= key[i] &&
						key[i] <= 'F') || ('0' <= key[i] && key[i] <= '9')))
			iv_error(dis);
	done = hex_to_l(key);
	free(key);
	return (done);
}

char			*ft_hardjoin(char *s1, int len1, char *s2, int len2)
{
	char	*new;

	new = ft_strnew(len1 + len2);
	ft_memcpy(new, s1, len1);
	ft_memcpy(new + len1, s2, len2);
	free(s1);
	return (new);
};
