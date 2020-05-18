/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:34:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/13 00:50:48 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "ft_ssl.h"
#include "ssl_md5_dispatch.h"
#include "ssl_md5_enums.h"

/*
** make sure p behaves as expected
*/

int				do_ssl(t_ssl_input *input, char *infile, int dis)
{
	void	*w;

	if (infile && !(input->infd = open(infile, O_RDONLY)))
		bad_input(infile);
	if (input->flags & (q | p) && (w = g_sslfuns[dis].hash(input)))
	{
		g_sslfuns[dis].printer(w);
		ft_putchar('\n');
	}
	else if (input->flags & r && (w = g_sslfuns[dis].hash(input)))
	{
		g_sslfuns[dis].printer(w);
		ft_printf(" %s\n", infile);
	}
	else if ((w = g_sslfuns[dis].hash(input)))
	{
		ft_printf("%s ", g_sslfuns[dis].print);
		input->flags & s ? ft_printf("(\"%s\") = ", input->sstring) :
			ft_printf("(%s) = ", infile ? infile : "stdin");
		g_sslfuns[dis].printer(w);
		ft_putchar('\n');
	}
	return (1);
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
			if (input->flags & p && do_ssl(input, NULL, dis))
				input->flags -= p;
		}
		else
		{
			input->flags &= ~nof;
			do_ssl(input, NULL, dis);
			while (j < input->args)
				do_ssl(input, av[j++], dis);
			return ;
		}
	}
	if (input->flags & nof)
		do_ssl(input, NULL, dis);
}

void			cipher_flags(char **av, t_ssl_input *input, int dis, int j)
{
	while (++j < input->args)
	{
		if (av[j][0] == '-')
		{
			input->flags |=
				cipher_flag_val(av[j], dis, g_sslfuns[dis].print);
			if (j + 1 < input->args)
				j += j_increment(input, av[j + 1], g_sslfuns[dis].print, dis);
		}
		else
			break ;
	}
	get_missing(input, dis);
	g_sslfuns[dis].hash(input);
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
		dis <= 4 ? ssl_flags(av, input, dis, 1) :
			cipher_flags(av, input, dis, 1);
		input_free(input);
	}
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}
