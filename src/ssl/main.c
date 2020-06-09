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

t_sslfuns g_sslfuns[] =
{
	{"md5", "MD5", &ft_md5, &print_md5},
	{"sha224", "SHA224", &ft_sha224, &print_sha224},
	{"sha256", "SHA256", &ft_sha256, &print_sha256},
	{"sha384", "SHA384", &ft_sha384, &print_sha384},
	{"sha512", "SHA512", &ft_sha512, &print_sha512},
	{"base64", "BASE64", &ft_base64, NULL},
	{"des", "DES", &ft_des_cbc, NULL},
	{"des-cbc", "DES-CBC", &ft_des_cbc, NULL},
	{"des-ecb", "DES-ECB", &ft_des_ecb, NULL},
	{NULL, NULL, NULL, NULL}
};

int				do_ssl(t_ssl_input *input, char *infile, int dis)
{
	void	*w;

	input->len = 0;
	input->len2 = 0;
	input->flags &= ~readed;
	if (infile && (input->infd = open(infile, O_RDONLY)) < 0)
		bad_input(infile);
	else if (input->flags & (q | p) && (w = g_sslfuns[dis].hash(input)))
	{
		g_sslfuns[dis].printer(w);
		ft_putchar('\n');
	}
	else if (input->flags & r && (w = g_sslfuns[dis].hash(input)))
	{
		g_sslfuns[dis].printer(w);
		input->flags & s ? ft_printf(" \"%s\"\n", input->sstring) : ft_printf(" %s\n", infile);
	}
	else if ((w = g_sslfuns[dis].hash(input)))
	{
		ft_printf("%s ", g_sslfuns[dis].print);
		input->flags & s ? ft_printf("(\"%s\") = ", input->sstring) :
			ft_printf("(%s) = ", infile ? infile : "stdin");
		g_sslfuns[dis].printer(w);
		ft_putchar('\n');
	}
	if (input->infd > STDERR_FILENO)
		close(input->infd);
	return (1);
}

int				parse_input(char **av, t_ssl_input *input, int dis, int j)
{
	input->flags &= ~nof;
	if (!(input->flags & dunp))
		do_ssl(input, NULL, dis);
	input->flags &= ~(p | dunp);
	while (j < input->args)
		do_ssl(input, av[j++], dis);
	return (j);
}

void			ssl_flags(char **av, t_ssl_input *input, int dis, int j)
{
	while (++j < input->args)
	{
		if (av[j][0] == '-' && (av[j][1] == 's' || ft_strlen(av[j]) == 2))
		{
			input->curr_flag = flag_val(av[j], dis, g_sslfuns[dis].print);
			if (input->curr_flag == s && (j + 1 < input->args ||
						av[j][chr_index(av[j], 's') + 1]))
				j += handle_string(av, j, input, dis);
			if ((input->flags & (p | dunp)) == p && do_ssl(input, NULL, dis))
				input->flags |= dunp;
			input->flags |= input->curr_flag;

		}
		else
			j = parse_input(av, input, dis, j);
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
			input->curr_flag =
				cipher_flag_val(av[j], dis, g_sslfuns[dis].print);
			if (j + 1 < input->args)
				j += j_increment(input, av[j + 1], g_sslfuns[dis].print, dis);
			input->flags |= input->curr_flag;
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
