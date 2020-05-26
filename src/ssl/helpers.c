/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:18:19 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/10 13:33:08 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

unsigned		flip_end(unsigned n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

unsigned long	flip_end_512(unsigned long n)
{
	return ((n >> 56) | ((n & 0xff000000000000) >> 40) |
			((n & 0xff0000000000) >> 24) | ((n & 0xff00000000) >> 8) |
			((n & 0xff000000) << 8) | ((n & 0xff0000) << 24) |
			((n & 0xff00) << 40) | (n << 56));
}

int				handle_string(char **av, int j, t_ssl_input *input, int dis)
{
	int			i;
	int			ret;
	int			pi;

	i = 0;
	pi = input->flags & p;
	input->flags &= (~nof & ~p);
	ret = 0;
	while (av[j][i] != 's')
		i++;
	if (av[j][i + 1])
	{
		input->sflag = av[j] + i + 1;
		input->sstring = av[j] + i + 1;
	}
	else if (j + 1 < input->args)
	{
		ret = 1;
		input->sflag = av[j + 1];
		input->sstring = av[j + 1];
	}
	do_ssl(input, NULL, dis);
	input->flags |= pi;
	return (ret);
}
