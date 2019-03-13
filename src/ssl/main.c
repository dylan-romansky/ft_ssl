/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:18:02 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/12 19:18:09 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int				main(int ac, char **av)
{
	if (ac >= 2)
	{
		ssl_flags(av, ac);
	}
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}
