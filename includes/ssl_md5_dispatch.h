/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_dispatch.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:29:03 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/17 16:03:28 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_DISPATCH_H
# define SSL_MD5_DISPATCH_H

typedef struct s_sslfuns	t_sslfuns;

t_sslfuns g_sslfuns[] =
{
	{"md5", "MD5", &ft_md5},
	{"sha224", "SHA224", &ft_sha224},
	{"sha256", "SHA256", &ft_sha256},
	{"sha384", "SHA384", &ft_sha384},
	{"sha512", "SHA512", &ft_sha512},
	{"base64", "BASE64", &ft_base64},
	{"des", "DES", &ft_des_cbc},
	{"des-cbc", "DES-CBC", &ft_des_cbc},
	{"des-ecb", "DES-ECB", &ft_des_ecb},
	{NULL, NULL, NULL}
};

#endif
