/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_caller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 21:02:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/26 13:29:02 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

char	*strip_nl(t_ssl_input *input)
{
	char	**stripped;
	char	*tmp;
	int		i;

	stripped = ft_strsplit(input->input, '\n');
	i = 0;
	free(input->input);
	input->input = stripped[0];
	while (stripped[++i])
	{
		tmp = ft_strjoin(input->input, stripped[i]);
		free(input->input);
		input->input = tmp;
	}
	return (input->input);
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
	input->input = strip_nl(input);
	if (input->flags & d)
		return (ft_base64_d(input->input, input->len));
	return (ft_base64_e(input->input, input->len));
}
