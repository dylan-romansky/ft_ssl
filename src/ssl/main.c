/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:34:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/13 15:17:26 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_ssl_md5.h"
#include "ssl_md5_dispatch.h"

/*
** consider moving flag struct into new file and using that for flag funcs
*/

void			do_ssl(int flags, char *input, int dis)
{
	char			*file;
	int				len;

	if (!(len = get_input(open(input, O_RDONLY), flags, input, &file)))
		bad_input(input);
	if (len)
	{
		if (flags & q)
			g_sslfuns[dis].hash(file, len);
		else if (flags & r)
		{
			g_sslfuns[dis].hash(file, len);
			ft_printf(" %s", input);
		}
		else
		{
			ft_printf("%s ", g_sslfuns[dis].print);
			flags & s ? ft_printf("(\"%s\") = ", input) :
				ft_printf("(%s) = ", input);
			g_sslfuns[dis].hash(file, len);
		}
		free(file);
		ft_printf("\n");
	}
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

	j = 1;
	flags = 0;
	len = 0;
	while (++j < ac)
	{
		if (av[j][0] == '-')
			flags |= flag_val(av[j] + 1, g_sslfuns[dis].print);
		else
			break ;
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

void			ssl_flags(char **av, int ac, int dis, int j)
{
	char			flags;

	flags = 0;
	while (++j < ac)
	{
		if (av[j][0] == '-' && (av[j][1] == 's' || ft_strlen(av[j]) == 2))
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
		else
		{
			while (j < ac)
				do_ssl(flags, av[j++], dis);
			return ;
		}
	}
	check_stdin(av, ac, dis);
}

int				main(int ac, char **av)
{
	int				dis;

	dis = 0;
	if (ac >= 2)
	{
		while (g_sslfuns[dis].name && ft_strcmp(av[1], g_sslfuns[dis].name))
			dis++;
		if (!g_sslfuns[dis].name)
			error_nodis(av[1]);
		dis < 4 ? ssl_flags(av, ac, dis, 1) : cypher_flags(av, ac, dis, 1);
	}
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}
