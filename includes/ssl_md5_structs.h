/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:04:59 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/06 22:35:30 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_STRUCTS_H
# define SSL_MD5_STRUCTS_H

typedef struct s_md5_words	t_md5_words;
typedef struct s_sha_words	t_sha_words;

struct	s_md5_words
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

struct	s_sha_words
{
	unsigned	r;
	unsigned	a;
	unsigned	b;
	unsigned	c;
	unsigned	d;
	unsigned	e;
	unsigned	f;
	unsigned	g;
	unsigned	h;
	unsigned	h0;
	unsigned	h1;
	unsigned	h2;
	unsigned	h3;
	unsigned	h4;
	unsigned	h5;
	unsigned	h6;
	unsigned	h7;
	unsigned	tmp1;
	unsigned	tmp2;
	unsigned	tmp3;
	unsigned	tmp4;
	unsigned	tmp5;
	unsigned	tmp6;
};

#endif
