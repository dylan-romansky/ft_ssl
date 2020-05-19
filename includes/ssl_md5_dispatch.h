/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_dispatch.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:29:03 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/18 17:53:22 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_DISPATCH_H
# define SSL_MD5_DISPATCH_H

typedef struct s_sslfuns	t_sslfuns;

struct	s_sslfuns
{
	char	*name;
	char	*print;
	void	*(*hash)(t_ssl_input *);
	void	(*printer)(void *);
};

#endif
