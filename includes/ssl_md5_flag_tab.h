/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_flag_tab.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:58:23 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/09 00:11:22 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_FLAG_TAB_H
# define SSL_MD5_FLAG_TAB_H
# include "ssl_md5_enums.h"

typedef struct s_sslflags	t_sslflags;

struct	s_sslflags
{
	char	flag;
	int		value;
};

#endif
