/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:18:19 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/12 19:33:24 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

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

int				stdin_check(void)
{
	char			buf[80];
	int				number;

	number = 0;
	scanf("%79s", buf);
	if (sscanf(buf, "%d", &number) == 1)
		return (1);
	return (0);
}

int				handle_string(char **av, int j, int flags, int dis)
{
	int			i;

	i = 0;
	while (av[j][i] != 's')
		i++;
	if (av[j][i + 1])
	{
		do_ssl(flags, av[j] + i + 1, dis);
		return (0);
	}
	else
		do_ssl(flags, av[j + 1], dis);
	return (1);
}

int				get_input(int fd, int flags, char *input, char **file)
{
	int				len;
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*content;

	if (flags & 8 && fd != 0)
	{
		*file = ft_strdup(input);
		return (ft_strlen(input));
	}
	content = ft_strnew(0);
	len = 0;
	if (fd == -1)
		return (0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		content = swap_n_free(ft_strjoin(content, buf), &content);
		len += ret;
	}
	if (ret < 0)
		free(content);
	*file = content;
	return (len);
}
