/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_n_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 15:34:38 by dromansk          #+#    #+#             */
/*   Updated: 2019/01/10 19:48:31 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*swap_n_free(char *new, char **old)
{
	char *tmp;

	tmp = NULL;
	if (old && *old)
		tmp = *old;
	if (new != tmp && tmp)
		free(tmp);
	return (new);
}
