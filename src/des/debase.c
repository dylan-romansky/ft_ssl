/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debase.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 23:00:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/14 00:45:42 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

void			debase64_des(t_ssl_input *input)
{
	ft_memcpy(input->base, input->input, input->len);
	ft_bzero(input->input, BUFF_SIZE);
	strip_nl(input);
	input->len = ft_strlen(input->base);
	while (input->read > 0 && input->len < BUFF_SIZE / 3 * 4)
	{
		input->read = read(input->infd, input->base + input->len, (BUFF_SIZE / 3 * 4) - input->len);
		strip_nl(input);
		input->len = ft_strlen(input->base);
	}
	ft_base64_d(input);
	ft_bzero(input->base, BUFF_SIZE / 3 * 4);
}
