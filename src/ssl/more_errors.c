/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:07:09 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/14 00:46:20 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des_len_error(int dis)
{
	if (dis == 6)
		ft_printf("Error: des: Message not multiple of block length.\n");
	if (dis == 7)
		ft_printf("Error: des-cbc: Message not multiple of block length.\n");
	if (dis == 8)
		ft_printf("Error: des-ecb: Message not multiple of block length.\n");
	exit(1);
}
