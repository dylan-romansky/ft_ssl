/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_caller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:02:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/30 23:50:05 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

char		*strip_nl(char *input)
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

int		ft_base64(t_ssl_input *input)
{
	unsigned char	*b;

	b = NULL;
	if (input->flags & d)
	{
		input->input = strip_nl(input->input);
		input->len = ft_strlen(input->input);
		b = ft_base64_d(input->input, input->len);
		write(input->outfd, b, (3 * (input->len / 4)) - minus_pad(input->input));
	}
	else
	{
		b = ft_base64_e(input->input, input->len);
		ft_putstr((char *)b);
	}
	return (1);
}
