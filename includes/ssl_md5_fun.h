/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_fun.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:08:20 by dromansk          #+#    #+#             */
/*   Updated: 2019/05/31 00:25:31 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_FUN_H
# define SSL_MD5_FUN_H
# include "ssl_md5_structs.h"

unsigned			flip_end(unsigned n);
unsigned long		flip_end_512(unsigned long n);

int					get_input(int fd, int flags, char *input, char **file);
t_ssl_input			*make_input(int ac);

void				flag_error(char *name, char *flag, int dis);
void				error_nodis(char *input);

void				ssl_flags(char **av, t_ssl_input *input, int dis, int j);
void				cipher_flags(char **av, t_ssl_input *input, int dis, int j);
int					flag_val(char *flags, int dis, char *fun);
int					cipher_flag_val(char *flags, int dis, char *fun);
int					j_increment(t_ssl_input *input, char *arg, char *fun,
		int dis);
int					input_file(t_ssl_input *input, char *name, char *fun,
		int fd);
int					output_file(t_ssl_input *input, char *path);
int					get_pass(t_ssl_input *input, char *pass);
unsigned long long	hex_to_l(char *st);

int					stdin_check(void);
void				bad_input(char *input);
void				no_file(char *name, char *fun);
void				no_read(char *name, char *fun);
void				get_missing(t_ssl_input *input, int dis);
void				des_len_error(int dis);

int					handle_string(char **av, int j, t_ssl_input *input,
		int dis);
void				do_ssl(t_ssl_input *input2, char *input, int dis);
char				*ft_hardjoin(char *s1, int len1, char *s2, int len2);

unsigned long		check_key(char *tmp, int dis);
unsigned long		verify_iv(char *tmp, int dis);
char				*pad_iv(char *s);
unsigned long		verify_salt(char *tmp, int dis);
void				pass_input(t_ssl_input *input);
unsigned long		gen_salt(void);
unsigned long		salt_pass(t_ssl_input *input, char *tmp,
		unsigned long salt);
void				input_free(t_ssl_input *input);

/*
** md5
*/

int					ft_md5(t_ssl_input *input);
void				hashing_functions_md5(t_md5_words *words, int i,
		unsigned *chunks);
uint32_t			left_rotate(uint32_t bits, uint32_t rot);
unsigned			flip_end(unsigned unflipped);
int					lessthan16(t_md5_words *words, int i);
int					lessthan32(t_md5_words *words, int i);
int					lessthan48(t_md5_words *words, int i);
int					upto64(t_md5_words *words, int i);
void				split_input_32(char *process, t_md5_words *words);

/*
** sha256 and sha224
*/

int					ft_sha256(t_ssl_input *input);
int					ft_sha224(t_ssl_input *input);
uint32_t			rightrotate(uint32_t input, uint32_t amount);
void				sha_process_chunk(char *chunk, t_sha_words *words);
int					sha_pad(char *input, unsigned len, t_sha_words *words);

/*
** sha512 and sha384
*/

int					ft_sha512(t_ssl_input *input);
int					ft_sha384(t_ssl_input *input);
void				process_chunk_512(char *chunk, t_512_words *words);
int					sha_pad_512(char *input, unsigned len, t_512_words *words);

/*
** base64
*/

int					ft_base64(t_ssl_input *input);
unsigned char		*ft_base64_e(char *input, size_t len);
unsigned char		*ft_base64_d(char *input, size_t len);
unsigned char		*expand_base(unsigned chunk);
unsigned char		*contract_base(unsigned chunk);
unsigned char		*char_swap(unsigned char *chunk, int p);
int					minus_pad(char *input);

/*
** des
*/

int					ft_des_cbc(t_ssl_input *input);
int					ft_des_ecb(t_ssl_input *input);
unsigned char		*ft_des_cbc_e(t_ssl_input *input);
unsigned char		*ft_des_cbc_d(t_ssl_input *input);
unsigned char		*ft_des_ecb_e(t_ssl_input *input);
unsigned char		*ft_des_ecb_d(t_ssl_input *input);
unsigned long		*gen_key(unsigned long key);
unsigned			key_encrypt(unsigned right, unsigned long key);
unsigned long		init_perm(unsigned long block);
unsigned long		split_perm_e(unsigned long perm, unsigned long *key48);
unsigned long		split_perm_d(unsigned long perm, unsigned long *key48);
unsigned long		reverse_permute(unsigned left, unsigned right);
const int			***init_boxes(void);

#endif
