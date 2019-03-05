/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:46:13 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/05 13:47:26 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

typedef enum e_argtype		t_argtype;
typedef enum e_argsize		t_argsize;

enum	e_argtype
{
	d = 0, D = 0, in = 0, o = 1, O = 1, u = 2, U = 2, x = 3, X = 4,
	b = 5, p = 6, st = 7, ch = 8, f = 9, F = 10, per = 11
};

enum	e_argsize
{
	none = 0, h = 1, hh = 2, l = 3, ll = 4, j = 5, z = 6, el = 7
};

#endif
