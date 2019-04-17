/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:34:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/16 20:51:29 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_ssl_md5.h"
#include "ssl_md5_dispatch.h"

/*
** consider moving flag struct into new file and using that for flag funcs
*/

void			do_ssl(t_ssl_input *input2, char *input, int dis)
{
	char			*file;

	if (!(input2->len = get_input(open(input, O_RDONLY),
					input2->flags, input, &file)))
		bad_input(input);
	if (input2->len)
	{
		input2->input = file;
		if (flags & q)
			g_sslfuns[dis].hash(input2);
		else if (flags & r)
		{
			g_sslfuns[dis].hash(input2);
			ft_printf(" %s", input);
		}
		else
		{
			ft_printf("%s ", g_sslfuns[dis].print);
			flags & s ? ft_printf("(\"%s\") = ", input) :
				ft_printf("(%s) = ", input);
			g_sslfuns[dis].hash(input2);
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

void			ssl_flags(char **av, t_ssl_input *input, int dis, int j)
{
	input->flags = 0;
	while (++j < input->args)
	{
		if (av[j][0] == '-' && (av[j][1] == 's' || ft_strlen(av[j]) == 2))
		{
			input->flags |= flag_val(av[j] + 1, g_sslfuns[dis].print);
			if (input->flags & s && (j + 1 < ac ||
						av[j][chr_index(av[j], 's') + 1]))
			{
				j += handle_string(av, j, flags, dis);
				input->flags -= s;
			}
			if (input->flags & p)
				input->flags -= check_stdin(av, ac, dis);
		}
		else
		{
			while (j < ac)
				do_ssl(input, av[j++], dis);
			return ;
		}
	}
	check_stdin(av, ac, dis);
}

int				main(int ac, char **av)
{
	int				dis;
	t_ssl_input		*input;

	dis = 0;
	if (ac >= 2)
	{
		input = make_input(ac);
		while (g_sslfuns[dis].name && ft_strcmp(av[1], g_sslfuns[dis].name))
			dis++;
		if (!g_sslfuns[dis].name)
			error_nodis(av[1]);
		dis < 4 ? ssl_flags(av, input, dis, 1) : cipher_flags(av, input, dis, 1);
		free(input);
	}
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}
