/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_fun.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:08:20 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/28 21:14:28 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_FUN_H
# define SSL_MD5_FUN_H

/*
** hashing functions
*/
unsigned char	b_or(unsigned char b, unsigned char c, unsigned char d);
unsigned char	d_or(unsigned char b, unsigned char c, unsigned char d);
unsigned char	bcd_xor(unsigned char b, unsigned char c, unsigned char d);
unsigned char	c_xor_b_or_nd(unsigned char b, unsigned char c, unsigned char d);

/*
** preprocessing
*/

void			pad_input(char *input);

#endif
