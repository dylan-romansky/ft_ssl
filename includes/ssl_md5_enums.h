/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_enums.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:00:01 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/18 17:48:38 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_ENUMS_H
# define SSL_MD5_ENUMS_H

typedef enum e_sslfenums	t_sslfenums;
typedef enum e_base64enums	t_base64enums;
typedef enum e_desenums		t_desenums;

enum	e_sslfenums
{
	p = 1, q = 2, r = 4, s = 8
};

enum	e_base64enums
{
	d = 16, e = 32, i = 64, o = 128
};

enum	e_desenums
{
	a = 256, k = 512, p2 = 1024, s2 = 2048, v = 4096
};

#endif
