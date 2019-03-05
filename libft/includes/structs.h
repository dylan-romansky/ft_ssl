/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:54:51 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/26 00:20:45 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "printf.h"

typedef struct s_flag		t_flag;
typedef struct s_stringmake	t_stringmake;
typedef struct s_numcon		t_numcon;
typedef struct s_arglen		t_arglen;
typedef struct s_types		t_types;

struct	s_flag
{
	int	sharp;
	int	zero;
	int	dash;
	int	plus;
	int	space;
	int	dot;
	int	prec;
	int	width;
	int	size;
	int	type;
};

struct	s_stringmake
{
	char	*(*string)(t_flag *, va_list *);
};

struct	s_numcon
{
	int		base;
	char	*(*data)(long long, int);
};

struct	s_arglen
{
	intmax_t	(*parse)(va_list *);
};
struct	s_types
{
	char	type;
	int		num;
};

#endif
