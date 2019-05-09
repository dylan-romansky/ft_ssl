/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:05:51 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 00:07:11 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_flag_tab.h"

int				flag_val(char *flags, int dis, char *fun)
{
	int				i;
	int				j;
	int				sum;

	i = 0;
	j = 0;
	sum = 0;
	if (flags[1] == '-')
		i++;
	while (flags[++i])
	{
		while (g_sslflags[j].flag && g_sslflags[j].flag != flags[i])
			j++;
		if (!g_sslflags[j].flag)
			flag_error(fun, flags, dis);
		sum |= g_sslflags[j].value;
		if (sum & s)
			return (sum);
	}
	return (sum);
}

int				des_flag_val(char *flags)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (flags[1] == '-')
		i++;
	while (g_desflags[j].flag && g_desflags[j].flag != flags[i])
		j++;
	return (g_desflags[j].flag ? g_desflags[j].value : -1);
}

int				cipher_flag_val(char *flags, int dis, char *fun)
{
	int				i;
	int				j;
	int				sum;

	i = 0;
	j = 0;
	sum = 0;
	if (flags[1] == '-')
		i++;
	while (flags[++i])
	{
		while (g_base64flags[j].flag && g_base64flags[j].flag != flags[i])
			j++;
		if (dis > 5)
			j = g_base64flags[j].flag ? g_base64flags[j].value :
			des_flag_val(flags);
		else
			j = g_base64flags[j].flag ? g_base64flags[j].value : -1;
		if (j < 0)
			flag_error(fun, flags, dis);
		sum |= j;
	}
	return (sum);
}
