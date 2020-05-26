/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:17:39 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 16:29:03 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	flag_error(char *name, char *flag, int dis)
{
	ft_dprintf(STDERR_FILENO, "%s: illegal option: %s\nusage: %s ", name, flag, name);
	if (dis <= 4)
		ft_dprintf(STDERR_FILENO, "[-pqr] [-s string] [files ...]\n");
	else if (dis == 5)
		ft_dprintf(STDERR_FILENO, "[-e | -d] [-i infile] [-o outfile]\n");
	else if (dis <= 8)
	{
		ft_dprintf(STDERR_FILENO, "[-e | -d] [-a] [-k key] [-v init vector] [-i infile]");
		ft_dprintf(STDERR_FILENO, " [-o outfile]\n");
	}
	exit(1);
}

void	error_nodis(char *input)
{
	ft_dprintf(STDERR_FILENO, "ft_ssl: Error: '%s' is an invalid command.\n\nStandard", input);
	ft_dprintf(STDERR_FILENO, " commands:\n\nMessage Digest commands:\nmd5\nsha224\nsha256\n");
	ft_dprintf(STDERR_FILENO, "sha384\nsha512\n\nCipher commands:\nbase64\ndes\ndes-ecb\n");
	ft_dprintf(STDERR_FILENO, "des-cbc\n");
	exit(1);
}

void	bad_input(char *input)
{
	ft_dprintf(STDERR_FILENO, "ft_ssl: md5: %s: No such file or directory\n", input);
}

void	no_file(char *input, char *fun)
{
	ft_dprintf(STDERR_FILENO, "%s: Error: can't open file: '%s'\n", fun, input);
	exit(1);
}

void	no_read(char *input, char *fun)
{
	ft_dprintf(STDERR_FILENO, "%s: Error: can't read file: '%s'\n", fun, input);
	exit(1);
}
