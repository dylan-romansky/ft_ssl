/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_base64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:02:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/14 01:01:28 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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

void	strip_nl(t_ssl_input *input)
{
	char	**stripped;
	int		i;
	int		len;
	int		total;

	if (!input->read)
		return ;
	stripped = ft_strsplit(input->base, '\n');
	i = 0;
	len = 0;
	total = 0;
	while (stripped[i])
	{
		len = ft_strlen(stripped[i]);
		ft_memcpy(input->base + total, stripped[i], len);
		total += len;
		free(stripped[i++]);
	}
	input->len = total;
	free(stripped);
}

int		read_base64_d(t_ssl_input *input)
{
	input->len = read(input->infd, input->base, BUFF_SIZE / 3 * 4);
	while (input->len > 0 && input->len < BUFF_SIZE / 3 * 4)
	{
		input->len += input->read;
		strip_nl(input);
		input->read = read(input->infd, input->base + input->len, (BUFF_SIZE / 3 * 4) - input->read);
	}
	return (input->len);
}
