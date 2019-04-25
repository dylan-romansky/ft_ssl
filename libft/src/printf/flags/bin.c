/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:54:24 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/24 19:06:23 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	fix_bin(t_flag **flags)
{
	t_flag	*curr;

	curr = *flags;
	curr->zero = 1;
	if (!(curr->width))
		curr->width++;
	while (curr->width % 8)
		curr->width++;
}
