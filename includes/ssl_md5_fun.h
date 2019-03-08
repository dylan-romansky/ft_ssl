/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_fun.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:08:20 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/07 23:06:29 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_FUN_H
# define SSL_MD5_FUN_H
# include "ssl_md5_structs.h"

unsigned	flip_end(unsigned n);

/*
** debugging functions
*/

void		force_print(char *s, int j);

/*
** md5
*/

int			ft_md5(char *input);
void		hashing_functions_md5(t_md5_words *words, int i, unsigned *chunks);
uint32_t	left_rotate(uint32_t bits, uint32_t rot);
unsigned	flip_end(unsigned unflipped);

/*
** sha256
*/

int			ft_sha256(char *input);
uint32_t	rightrotate(uint32_t input, uint32_t amount);
void		sha_process_chunk(char *chunk, t_sha_words *words);

#endif
