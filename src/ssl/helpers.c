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
/*does this even get used?
int				stdin_check(void)
{
	char			buf[80];
	int				number;

	number = 0;
	scanf("%79s", buf);
	if (sscanf(buf, "%d", &number) == 1)
		return (1);
	return (0);
}*/

int				handle_string(char **av, int j, t_ssl_input *input, int dis)
{
	int			i;
	int			ret;

	i = 0;
	input->flags &= ~nof;
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
// verify how other ssl projects handle an -s with no string
// for bufferization with string input, consider copying into
// the buffer BUFF_SIZE at a time and running it through
	do_ssl(input, NULL, dis);
	input->sflag = NULL;
	input->sstring = NULL;
	return (ret);
}

/*
int				get_input(int fd, char *input, char **file)
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
	len = 0;
	if (fd == -1)
		return (0);
	content = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		content = ft_hardjoin(content, len, buf, ret);
		len += ret;
	}
	if (ret < 0)
		free(content);
	*file = content;
	return (len);
}*/
