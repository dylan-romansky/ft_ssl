/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 17:07:09 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 17:08:32 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	des_len_error(int dis)
{
	if (dis == 6)
		ft_printf("Error: des: Message not multiple of block length.");
	if (dis == 7)
		ft_printf("Error: des-cbc: Message not multiple of block length.");
	if (dis == 8)
		ft_printf("Error: des-ecb: Message not multiple of block length.");
	exit(1);
}
