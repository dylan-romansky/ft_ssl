/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_caller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:02:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/14 01:01:28 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

int		minus_pad(char *input)
{
	int		i;

	i = 0;
	while (*input)
		if (*input++ == '=')
			i++;
	return (i);
}

void	print_base64(char *s, int fd, size_t len)
{
	size_t	i;

	i = 0;
	while (i + 64 < len)
	{
		write(fd, s + i, 64);
		write(fd, "\n", 1);
		i += 64;
	}
	ft_putendl_fd(s + i, fd);
}

void	*ft_base64(t_ssl_input *input)
{
	unsigned char	*b;

	b = NULL;
	if (input->flags & d)
	{
		while (read_base64_d(input))
		{
			verify_base64(input->input);
			ft_base64_d(input);
			write(input->outfd, input->input,
					(input->len * 3 / 4) -
					minus_pad(input->base));
		}
	}
	else
	{
		while ((input->read = read(input->infd, input->input, BUFF_SIZE)))
			ft_base64_e(input);
		print_base64((char *)b, input->outfd, ft_strlen((char *)b));
	}
	return (0);
}
