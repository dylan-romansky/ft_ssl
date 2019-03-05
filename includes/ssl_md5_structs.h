/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:04:59 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/28 02:07:51 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_STRUCTS_H
# define SSL_MD5_STRUCTS_H

typedef struct s_hashfun	t_hashfun;

struct s_hashfun
{
	unsigned char	(*hash)(unsigned char, unsigned char, unsigned char);
};

#endif
