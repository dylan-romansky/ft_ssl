/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstruct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:34:34 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/05 16:25:32 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTSTRUCT_H
# define PRINTSTRUCT_H
# include "printf.h"

t_stringmake g_string[] =
{
	{&parse_numbers},
	{&parse_pointer},
	{&parse_chars},
	{&parse_float}
};

t_numcon g_numconvert[] =
{
	{10, &ft_imaxtoa_base},
	{8, &ft_uimaxtoa_base},
	{10, &ft_uimaxtoa_base},
	{16, &ft_uimaxtoa_base},
	{16, &ft_uimaxtoa_base},
	{2, &ft_uimaxtoa_base},
	{10, &ft_uimaxtoa_base}
};

t_arglen g_arglen[] =
{
	{&get_normal},
	{&get_h},
	{&get_hh},
	{&get_l},
	{&get_ll},
	{&get_j},
	{&get_z}
};

t_arglen g_uarglen[] =
{
	{&uget_normal},
	{&uget_h},
	{&uget_hh},
	{&uget_l},
	{&uget_ll},
	{&uget_j},
	{&uget_z}
};

#endif
