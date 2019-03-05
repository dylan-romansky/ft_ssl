/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 15:07:01 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/05 16:52:52 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H

typedef struct s_colour	t_colour;

struct	s_colour
{
	char	*colour;
	char	*code;
};

t_colour g_colour[] =
{
	{"red", "\033[0;31m"},
	{"green", "\033[0;32m"},
	{"yellow", "\033[0;33m"},
	{"blue", "\033[0;34m"},
	{"magenta", "\033[0;35m"},
	{"cyan", "\033[0;36m"},
	{"eoc", "\033[0m"}
};

#endif
