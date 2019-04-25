/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:35:00 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/24 18:23:06 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** write flag getting function for ciphers
** ciphers default to encryption
*/

t_ssl_input	*make_input(int ac)
{
	t_ssl_input	*input;

	if (!(input = (t_ssl_input *)malloc(sizeof(t_ssl_input))))
		return (NULL);
	input->args = ac;
	input->input = NULL;
	input->len = 0;
	input->flags = 0;
	input->infd = 0;
	input->outfd = 0;
	input->key = 0;
	return (input);
}
