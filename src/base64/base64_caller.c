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

void	verify_base64(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (!(('a' <= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z') ||
				('0' <= s[i] && s[i] <= '9') || s[i] == '+' || s[i] == '/' ||
				s[i] == '='))
		{
			ft_printf("error: non-base64 character detected\n");
			exit(1);
		}
}

char	*strip_nl(char *input)
{
	char	**stripped;
	char	*tmp;
	int		i;

	stripped = ft_strsplit(input, '\n');
	i = 0;
	free(input);
	input = stripped[0];
	while (stripped[++i])
	{
		tmp = ft_strjoin(input, stripped[i]);
		free(input);
		input = tmp;
	}
	return (input);
}

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

int		ft_base64(t_ssl_input *input)
{
	unsigned char	*b;

	b = NULL;
	if (input->flags & d)
	{
		input->input = strip_nl(input->input);
		verify_base64(input->input);
		input->len = ft_strlen(input->input);
		b = ft_base64_d(input->input, input->len);
		write(input->outfd, b, (3 * (input->len / 4)) -
				minus_pad(input->input));
	}
	else
	{
		b = ft_base64_e(input->input, input->len);
		print_base64((char *)b, input->outfd, ft_strlen((char *)b));
	}
	return (1);
}
