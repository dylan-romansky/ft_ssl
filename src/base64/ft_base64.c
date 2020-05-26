/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:16:47 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/14 00:29:07 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned		get_chunk(char *input, int i, int len, int size)
{
	unsigned		chunk;

	chunk = 0;
	if (i < (len - size - 1))
		ft_memcpy(&chunk, input + i, size);
	else
		ft_memcpy(&chunk, input + i, len - i);
	return (chunk);
}

void			ft_base64_e(t_ssl_input *input)
{
	int				chunk;
	int				i;
	unsigned char	e[4];

	i = 0;
	while (i < input->read)
	{
		chunk = get_chunk(input->input, i, input->read, i < input->read - 2 ? 3 : input->read - i);
		ft_bzero(e, 4);
		expand_base(chunk, e);
		i += 3;
		char_swap(e, i > input->read ? i - input->read : 0);
		ft_memcpy(input->base + (i / 3 * 4) - 4, e, 4);
	}
	input->len = input->read / 3 * 4;
}

void			ft_base64_d(t_ssl_input *input)
{
	int				chunk;
	size_t			i;
	int				dif;
	unsigned char	d[3];

	chunk = 0;
	i = 0;
	dif = minus_pad(input->base);
	input->len -= dif;
	while (i < input->len)
	{
		ft_bzero(d, 3);
		chunk = get_chunk(input->base, i, input->len, i < input->len - 3 ? 4 : input->len - i);
		contract_base(chunk, d);
		ft_memcpy(input->input + (i * 3 / 4), d, (i + 4) > input->len ? input->len - i : 3);
		i += 4;
	}
	input->len = (i * 3 / 4) - dif;
}
