/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:16:47 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/30 20:40:14 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
/*
** issue found with encryption
*/
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

void		print_chunk(unsigned char *chunk, int i, int p, int fd)
{
	int		size;

	size = 4;
	while (size-- > p)
	{
		if (*chunk < 26)
			ft_dprintf(fd, "%c", 'A' + *chunk);
		else if (*chunk < 52)
			ft_dprintf(fd, "%c", 'a' + (*chunk - 26));
		else if (*chunk < 62)
			ft_dprintf(fd, "%c", '0' + (*chunk - 52));
		else if (*chunk < 64)
			ft_dprintf(fd, "%c", (*chunk - 62) ? '/' : '+');
		chunk++;
		i++;
	}
	write(fd, "==", p);
}

unsigned	get_chunk(char *input, int i, int len, int size)
{
	unsigned		chunk;

	chunk = 0;
	if (i < (len - size - 1))
		ft_memcpy(&chunk, input + i, size);
	else
		ft_memcpy(&chunk, input + i, len - i);
	return (chunk);
}

int			ft_base64_e(char *input, size_t len, int fd)
{
	int				chunk;
	size_t			i;
	unsigned char	*e;

	chunk = 0;
	i = 0;
	while (input[i])
		ft_printf("%b ", input[i++]);
	ft_printf("\n");
	i = 0;
	while (i < len)
	{
		chunk = get_chunk(input, i, len, i < len - 2 ? 3 : len - i);
		e = expand_base(chunk);
		print_chunk(e, i, i > len ? (i - len) : 0, fd);
		i += 3;
	}
	return (1);
}

int			ft_base64_d(char *input, size_t len, int fd)
{
	int				chunk;
	size_t			i;
	unsigned char	*d;

	input = strip_nl(input);
	chunk = 0;
	i = 0;
	while (input[i])
		ft_printf("%b ", input[i++]);
	ft_printf("\n");
	i = 0;
	len -= minus_pad(input);
	while (i < len)
	{
		chunk = get_chunk(input, i, len, i < len - 3 ? 4 : len - i);
		d = contract_base(chunk);
		decrypt_chunk(d, 3, i > len ? (i - len) : 0, fd);
		i += 4;
	}
	return (1);
}
