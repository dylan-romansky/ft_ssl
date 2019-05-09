/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:34:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 00:15:11 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_ssl.h"
#include "ssl_md5_dispatch.h"
#include "ssl_md5_enums.h"

void			do_ssl(t_ssl_input *input2, char *input, int dis)
{
	char			*file;

	if (!(input2->len = get_input(open(input, O_RDONLY),
					input2->flags, input, &file)))
		bad_input(input);
	if (input2->len)
	{
		input2->input = file;
		if (input2->flags & q)
			g_sslfuns[dis].hash(input2);
		else if (input2->flags & r)
		{
			g_sslfuns[dis].hash(input2);
			ft_printf(" %s", input);
		}
		else
		{
			ft_printf("%s ", g_sslfuns[dis].print);
			input2->flags & s ? ft_printf("(\"%s\") = ", input) :
				ft_printf("(%s) = ", input);
			g_sslfuns[dis].hash(input2);
		}
		free(file);
		ft_printf("\n");
	}
}

int				check_stdin(t_ssl_input *input, int dis)
{
	char	*file;

	file = NULL;
	fcntl(0, F_SETFL, O_NONBLOCK);
	input->len = get_input(0, input->flags, NULL, &file);
	if (input->len)
	{
		input->input = file;
		if (input->flags & p)
			ft_printf("%s", file);
		g_sslfuns[dis].hash(input);
		ft_printf("\n");
		free(file);
	}
	return (p);
}

void			ssl_flags(char **av, t_ssl_input *input, int dis, int j)
{
	while (++j < input->args)
	{
		if (av[j][0] == '-' && (av[j][1] == 's' || ft_strlen(av[j]) == 2))
		{
			input->flags |= flag_val(av[j], dis, g_sslfuns[dis].print);
			if (input->flags & s && (j + 1 < input->args ||
						av[j][chr_index(av[j], 's') + 1]))
			{
				j += handle_string(av, j, input, dis);
				input->flags -= s;
			}
			if (input->flags & p)
				input->flags -= check_stdin(input, dis);
		}
		else
		{
			while (j < input->args)
				do_ssl(input, av[j++], dis);
			return ;
		}
	}
	check_stdin(input, dis);
}

void			cipher_flags(char **av, t_ssl_input *input, int dis, int j)
{
	while (++j < input->args)
	{
		if (av[j][0] == '-')
		{
			j += cipher_flag_val(av[j], dis, g_ssluns[dis].print, input);
/*			if (flags & i)
				j += input_file(input, av[j]);
			if (flags & o)
				j += output_file(input, av[j]);
			if (flags & k)
				j += hex_to_l(input, av[j]);
			if (flags & p2)
				j += get_pass(input, av[j]);
			if (flags & s2)
				j += hex_to_l(input, av[j]);
			if (flags & v)
				j += hex_to_l(input, av[j]);
commented out but saving cuz I'll need these checks for the cipher_flag_val deal
check can use xor to see if any flags are missing
*/
		}
		else
			break ;
	}
	get_missing(input, g_ssl_funs[dis].hash);
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
		dis < 4 ? ssl_flags(av, input, dis, 1) :
			cipher_flags(av, input, dis, 1);
		free(input);
	}
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}
