/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_caller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:02:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/18 18:10:42 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include "ssl_md5_enums.h"

/*
** write function to strip decryption input of newlines
*/

int		ft_base64(t_ssl_input *input)
{
	if (input->flags & d)
		return (ft_base64_d(input->input, input->len));
	return (ft_base64_e(input->input, input->len));
}
