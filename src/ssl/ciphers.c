/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ciphers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 20:35:00 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/22 16:10:34 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

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
	input->len = 0;
	input->len2 = 0;
	input->flags = nof;
	input->infd = STDIN_FILENO;
	input->outfd = STDOUT_FILENO;
	input->key = 0;
	input->iv = 0;
	input->salt = 0;
	input->pass = NULL;
	input->sflag = NULL;
	input->sstring = NULL;
	return (input);
}

char		*pad_iv(char *s)
{
	char	*n;

	n = ft_strdup(s);
	while (ft_strlen(n) < 16)
		n = ft_hardjoin(n, ft_strlen(n), "0", 1);
	return (n);
}

void		input_free(t_ssl_input *input)
{
	ft_bzero(input->input, BUFF_SIZE);
	ft_bzero(input->base, BUFF_SIZE / 3 * 4);
	if (input->pass)
		free(input->pass);
	free(input);
}
