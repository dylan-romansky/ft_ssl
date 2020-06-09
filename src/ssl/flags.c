/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:05:51 by dromansk          #+#    #+#             */
/*   Updated: 2019/06/07 16:44:17 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_flag_tab.h"

t_sslflags g_sslflags[] =
{
	{'p', p},
	{'q', q},
	{'r', r},
	{'s', s},
	{'\0', 0}
};

t_sslflags g_base64flags[] =
{
	{'d', d},
	{'e', e},
	{'i', i},
	{'o', o},
	{'\0', 0}
};

t_sslflags g_desflags[] =
{
	{'a', a},
	{'k', k},
	{'p', p2},
	{'s', s2},
	{'v', v},
	{'\0', 0}
};

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

	i = flags[0] == '-' && flags[1] == '-' ? 2 : 1;
	j = 0;
	while (g_desflags[j].flag && g_desflags[j].flag != flags[i])
		j++;
	return (g_desflags[j].flag ? g_desflags[j].value : -1);
}

int				cipher_flag_val(char *flags, int dis, char *fun)
{
	int				i;
	int				j;
	int				sum;

	i = flags[0] == '-' && flags[1] == '-' ? 2 : 1;
	j = 0;
	if (ft_strlen(flags + i) > 2)
		flag_error(fun, flags, dis);
	while (g_base64flags[j].flag && g_base64flags[j].flag != flags[i])
		j++;
	if (dis > 5)
		j = g_base64flags[j].flag ? g_base64flags[j].value :
		des_flag_val(flags);
	else
		j = g_base64flags[j].flag ? g_base64flags[j].value : -1;
	if (j < 0)
		flag_error(fun, flags, dis);
	sum = j;
	return (sum);
}

int				j_increment(t_ssl_input *input, char *arg, char *fun, int dis)
{
	if (input->curr_flag == i && input->infd == STDIN_FILENO)
		return (input_file(input, arg, fun, open(arg, O_RDONLY)));
	if (input->curr_flag == o && input->outfd == STDOUT_FILENO)
		return (output_file(input, arg));
	if (input->curr_flag == k && !input->key)
	{
		input->key = check_key(arg, dis);
		return (1);
	}
	if (input->curr_flag == p2 && !input->pass)
	{
		input->pass = ft_strdup(arg);
		return (1);
	}
	if (input->curr_flag == s2 && !input->salt)
	{
		input->salt = verify_salt(arg, dis);
		return (1);
	}
	if (input->curr_flag == v && !input->iv)
	{
		input->iv = verify_iv(arg, dis);
		return (1);
	}
	return (0);
}
