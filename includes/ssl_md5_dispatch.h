/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_dispatch.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:29:03 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/13 14:29:12 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_DISPATCH_H
# define SSL_MD5_DISPATCH_H

typedef enum e_sslfenums	t_sslfenums;
typedef struct s_sslflags	t_sslflags;
typedef struct s_sslfuns	t_sslfuns;

enum	e_sslfenums
{
	p = 1, q = 2, r = 4, s = 8, d = 16, e = 32, i = 64, o = 128, a = 256,
	k = 512, v = 1024
};

struct	s_sslflags
{
	char	flag;
	int		value;
};

struct	s_sslfuns
{
	char	*name;
	char	*print;
	int		(*hash)(char *, size_t);
};

t_sslflags g_sslflags[] =
{
	{'p', p},
	{'q', q},
	{'r', r},
	{'s', s},
	{'d', d},
	{'e', e},
	{'i', i},
	{'o', o},
	{'a', a},
	{'k', k},
	{'v', v},
	{'\0', 0}
};

t_sslfuns g_sslfuns[] =
{
	{"md5", "MD5", &ft_md5},
	{"sha224", "SHA224", &ft_sha224},
	{"sha256", "SHA256", &ft_sha256},
	{"sha384", "SHA384", &ft_sha384},
	{"sha512", "SHA512", &ft_sha512},
	{"base64", "BASE64", &ft_base64_e},
	{"base64", "BASE64", &ft_base64_d},
	{"des", "DES", &ft_des_cbc},
	{"des-cbc", "DES-CBC", &ft_des_cdc},
	{"des-ecb", "DES-ECB", &ft_des_ecb},
	{NULL, NULL, NULL}
};

#endif
