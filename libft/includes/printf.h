/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:47:32 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/28 16:57:02 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>
# include <fcntl.h>
# include "libft.h"
# include "structs.h"
# define INTMAX_T T_INTMAX

/*
** add %k for date printing YYYYMMDDHHMM
*/

/*
**printf main function
*/
int			ft_printf(const char *restrict format, ...);
int			ft_dprintf(int fd, const char *restrict format, ...);
int			make_string(const char *restrict format, va_list *args, int fd);
/*
**flags related functions
*/
int			initflags(t_flag **input);
int			set_flags(t_flag **flags, char *format, va_list *args);
int			set_first(t_flag **input, char *format);
int			set_width(t_flag **input, char *format, va_list *args);
int			set_length(t_flag **input, char *format);
int			set_first(t_flag **input, char *format);
int			set_more_flags(t_flag **flags, char *format, va_list *args);
int			set_type(t_flag **input, char *format);
void		fix_bin(t_flag **flags);
int			is_flag(char form, char *flags);
int			skip_nums(char *format);
int			flag_skip(char *format);
void		flag_del(t_flag **flags);
/*
**number conversion
*/
char		*ft_uimaxtoa_base(long long n, int base);
char		*ft_imaxtoa_base(long long n, int base);
/*
**functions used in parsing
*/
int			convert_type_num(int i);
int			parse_arg(t_flag *flags, va_list *args, char **buf);
char		*parse_numbers(t_flag *flags, va_list *args);
char		*parse_chars(t_flag *flags, va_list *args);
char		*parse_float(t_flag *flags, va_list *args);
char		*parse_pointer(t_flag *flags, va_list *args);
/*
**functions used to get actual data
*/
char		*get_char(va_list *args);
char		*get_string(va_list *args);
intmax_t	get_normal(va_list *args);
intmax_t	get_h(va_list *args);
intmax_t	get_hh(va_list *args);
intmax_t	get_l(va_list *args);
intmax_t	get_ll(va_list *args);
intmax_t	get_j(va_list *args);
intmax_t	get_z(va_list *args);
intmax_t	uget_normal(va_list *args);
intmax_t	uget_h(va_list *args);
intmax_t	uget_hh(va_list *args);
intmax_t	uget_l(va_list *args);
intmax_t	uget_ll(va_list *args);
intmax_t	uget_j(va_list *args);
intmax_t	uget_z(va_list *args);
/*
**functions used to reformat the data in accordance with the given flags
*/
int			format_string(char *st, t_flag *flags, char **buf, int t);
int			prec(char *format, va_list *args, t_flag **input);
char		*handle_precision(char *st, t_flag *flags, int t);
char		*neg_prec(char *st, t_flag *flags, int t);
int			float_check(char *st);
char		*null_cases(int t);
char		*format_alt(char *st, t_flag *flags, int t);
char		*handle_width(char *st, t_flag *flags, int t);
char		*joining(char **string, char **buf, int len, int buflen);
int			find_size(t_flag *flags, char *str, int t);
int			nullcheck(char *st);
char		*handle_width(char *st, t_flag *flags, int t);
char		*neg_width(char *st, t_flag *flags, int t);
char		*space_z(char *st, t_flag *flags);
int			check_flag(char *format);
int			error_handle(char **buf);
int			get_colour(char *format, char **buf);
int			colour_skip(char *format);
int			iscolour(char *format);

#endif
