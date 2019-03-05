/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:15:26 by dromansk          #+#    #+#             */
/*   Updated: 2018/11/29 20:25:03 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int square)
{
	int		root;

	root = 0;
	while (root * root != square && root < square / 2)
		root++;
	if (root * root != square)
		return (0);
	return (root);
}
