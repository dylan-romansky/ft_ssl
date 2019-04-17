/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_caller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:02:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/16 21:02:33 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** write function to strip decryption input of newlines
*/

int		ft_base64(t_ssl_input *input)
{
	if (input->decrypt)
		return (ft_base64_d(input->input, input->len));
	return (ft_base64_e(input->input, input->len));
}
