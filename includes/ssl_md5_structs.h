/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:04:59 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/06 18:37:45 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_STRUCTS_H
# define SSL_MD5_STRUCTS_H

typedef struct s_words	t_words;

struct	s_words
{
	unsigned	f;
	unsigned	a;
	unsigned	b;
	unsigned	c;
	unsigned	d;
	unsigned	a0;
	unsigned	b0;
	unsigned	c0;
	unsigned	d0;
};

#endif
