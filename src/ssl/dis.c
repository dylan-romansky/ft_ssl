/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:34:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/12 19:35:10 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_ssl_md5.h"
#include "ssl_md5_dispatch.h"

void			print_ssl(int flags, char *input, char *file, int dis)
{
	int				len;

	len = 0;
	if (!(len = get_input(open(input, O_RDONLY), flags, input, &file)))
	{
		bad_input(input);
		return ;
	}
	if (!(flags & q))
	{
		if (flags & r)
		{
			g_sslfuns[dis].hash(file, len);
			ft_printf(" %s", input);
		}
		else if (flags & s)
		{
			ft_printf("%s (\"%s\") = ", g_sslfuns[dis].print, input);
			g_sslfuns[dis].hash(file, len);
		}
		else
		{
			ft_printf("%s (%s) = ", g_sslfuns[dis].print, input);
			g_sslfuns[dis].hash(file, len);
		}
	}
	else
		g_sslfuns[dis].hash(file, len);
}

void			do_ssl(int flags, char *input, int dis)
{
	char			*file;

	print_ssl(flags, input, file, dis);
	free(file);
	ft_printf("\n");
}

int				flag_val(char *flags, char *fun)
{
	int				i;
	int				j;
	int				sum;

	i = -1;
	j = 0;
	sum = 0;
	if (flags[0] == '-')
		i++;
	while (flags[++i])
	{
		while (g_sslflags[j].flag && g_sslflags[j].flag != flags[i])
			j++;
		if (!g_sslflags[j].flag)
			flag_error(fun, flags[i]);
		sum |= g_sslflags[j].value;
		if (sum & s)
			return (sum);
	}
	return (sum);
}

int				check_stdin(char **av, int ac, int dis)
{
	char			*file;
	int				len;
	int				j;
	int				flags;

	j = 2;
	flags = 0;
	len = 0;
	while (j < ac)
	{
		if (av[j][0] == '-')
			flags |= flag_val(av[j] + 1, g_sslfuns[dis].print);
		else
			break ;
		j++;
	}
	fcntl(0, F_SETFL, O_NONBLOCK);
	len = get_input(0, flags, NULL, &file);
	if (len)
	{
		if (flags & p)
			ft_printf("%s", file);
		g_sslfuns[dis].hash(file, len);
		ft_printf("\n");
	}
	return (p);
}

void			ssl_flags(char **av, int ac)
{
	char			flags;
	int				j;
	int				dis;

	j = 1;
	flags = 0;
	dis = 0;
	while (g_sslfuns[dis].name && ft_strcmp(av[1], g_sslfuns[dis].name))
		dis++;
	if (!g_sslfuns[dis].name)
		error_nodis(av[1]);
	while (++j < ac)
	{
		if (av[j][0] == '-')
		{
			flags |= flag_val(av[j] + 1, g_sslfuns[dis].print);
			if (flags & s && (j + 1 < ac || av[j][chr_index(av[j], 's') + 1]))
			{
				j += handle_string(av, j, flags, dis);
				flags -= s;
			}
			if (flags & p)
				flags -= check_stdin(av, ac, dis);
		}
		else if (av[j][0] != '-')
		{
			while (j < ac)
				do_ssl(flags, av[j++], dis);
			return ;
		}
	}
	check_stdin(av, ac, dis);
}
