/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:16:06 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/13 14:23:30 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int		lessthan16(t_md5_words *words, int i)
{
	words->f = (words->b & words->c) | (~words->b & words->d);
	return (i);
}

int		lessthan32(t_md5_words *words, int i)
{
	words->f = (words->b & words->d) | (words->c & ~words->d);
	return ((5 * i + 1) % 16);
}

int		lessthan48(t_md5_words *words, int i)
{
	words->f = words->b ^ words->c ^ words->d;
	return ((3 * i + 5) % 16);
}

int		upto64(t_md5_words *words, int i)
{
	words->f = words->c ^ (words->b | ~words->d);
	return ((7 * i) % 16);
}
