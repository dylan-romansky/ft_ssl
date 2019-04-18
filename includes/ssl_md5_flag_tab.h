/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_flag_tab.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:58:23 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/17 16:02:54 by dromansk         ###   ########.fr       */
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

t_sslflags g_sslflags[] =
{
	{'p', p},
	{'q', q},
	{'r', r},
	{'s', s},
	{'\0', 0}
};

t_sslflags g_base64flags[] =
{
	{'d', d},
	{'e', e},
	{'i', i},
	{'o', o},
	{'\0', 0}
};

t_sslflags g_desflags[] =
{
	{'a', a},
	{'k', k},
	{'p', p2},
	{'s', s2},
	{'v', v},
	{'\0', 0}
}

#endif
