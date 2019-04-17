/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_fun.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:08:20 by dromansk          #+#    #+#             */
/*   Updated: 2019/04/10 22:13:02 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_FUN_H
# define SSL_MD5_FUN_H
# include "ssl_md5_structs.h"

unsigned		flip_end(unsigned n);
unsigned long	flip_end_512(unsigned long n);
int				get_input(int fd, int flags, char *input, char **file);
void			flag_error(char *name, char flag);
void			error_nodis(char *input);
void			ssl_flags(char **av, int ac, int dis, int j);
void			cypher_flags(char **av, int ac, int dis, int j);
int				stdin_check(void);
void			bad_input(char *input);
int				handle_string(char **av, int j, int flags, int dis);
void			do_ssl(int flags, char *input, int dis);

/*
** md5
*/

int				ft_md5(char *input, size_t len);
void			hashing_functions_md5(t_md5_words *words, int i,
		unsigned *chunks);
uint32_t		left_rotate(uint32_t bits, uint32_t rot);
unsigned		flip_end(unsigned unflipped);
int				lessthan16(t_md5_words *words, int i);
int				lessthan32(t_md5_words *words, int i);
int				lessthan48(t_md5_words *words, int i);
int				upto64(t_md5_words *words, int i);

/*
** sha256 and sha224
*/

int				ft_sha256(char *input, size_t len);
int				ft_sha224(char *input, size_t len);
uint32_t		rightrotate(uint32_t input, uint32_t amount);
void			sha_process_chunk(char *chunk, t_sha_words *words);
int				sha_pad(char *input, unsigned len, t_sha_words *words);

/*
** sha512 and sha384
*/

int				ft_sha512(char *input, size_t len);
int				ft_sha384(char *input, size_t len);
void			process_chunk_512(char *chunk, t_512_words *words);
int				sha_pad_512(char *input, unsigned len, t_512_words *words);

/*
** base64
*/

int				ft_base64_e(char *input, size_t len);
int				ft_base64_d(char *input, size_t len);
unsigned char	remove_chars(char c);
void			decrypt_chunk(unsigned char *d);

/*
** des_cdc
*/

int				ft_des_cbc(char *input, size_t len);

/*
** des_ecb
*/

int				ft_des_ecb(char *input, size_t len);

#endif
