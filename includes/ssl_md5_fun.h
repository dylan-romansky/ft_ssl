/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5_fun.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:08:20 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/14 00:58:17 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_FUN_H
# define SSL_MD5_FUN_H
# include "ssl_md5_structs.h"

unsigned			flip_end(unsigned n);
unsigned long		flip_end_512(unsigned long n);

int					read_hash(t_ssl_input *input, void *w, void (*pad)(t_ssl_input *, void *));
int					get_input(int fd, char *input, t_ssl_input *i);
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
unsigned char		*append_salt(unsigned char *s, t_ssl_input *input);
unsigned long long	hex_to_l(char *st);

int					stdin_check(void);
void				bad_input(char *input);
void				no_file(char *name, char *fun);
void				no_read(char *name, char *fun);
void				get_missing(t_ssl_input *input, int dis);
void				des_len_error(int dis);

int					handle_string(char **av, int j, t_ssl_input *input,
		int dis);
int					do_ssl(t_ssl_input *input, char *infile, int dis);
char				*ft_hardjoin(char *s1, int len1, char *s2, int len2);

unsigned long		check_key(char *tmp, int dis);
unsigned long		verify_iv(char *tmp, int dis);
char				*pad_iv(char *s);
unsigned long		verify_salt(char *tmp, int dis);
void				pass_input(t_ssl_input *input);
void				debase64_des(t_ssl_input *input);
void				strip_nl(t_ssl_input *input);
void				print_base64(char *s, int fd, size_t len);
void				desalt_des(t_ssl_input *input);
unsigned long		gen_salt(void);
unsigned long		salt_pass(t_ssl_input *input, char *tmp,
		unsigned long salt);
void				input_free(t_ssl_input *input);

/*
** md5
*/

void				*ft_md5(t_ssl_input *input);
void				hashing_functions_md5(t_md5_words *words, int i,
		unsigned *chunks);
uint32_t			left_rotate(uint32_t bits, uint32_t rot);
unsigned			flip_end(unsigned unflipped);
int					lessthan16(t_md5_words *words, int i);
int					lessthan32(t_md5_words *words, int i);
int					lessthan48(t_md5_words *words, int i);
int					upto64(t_md5_words *words, int i);
void				split_input_32(char *process, t_md5_words *words);
void				print_md5(void *w);
void				print_sha256(void *w);
void				print_sha224(void *w);
void				print_sha384(void *w);
void				print_sha512(void *w);

/*
** sha256 and sha224
*/

void				*ft_sha256(t_ssl_input *input);
void				*ft_sha224(t_ssl_input *input);
//int					sha_pad(char *input, unsigned len, t_sha_words *words);
int					read_sha(t_ssl_input *input, t_sha_words *w);
void				split_padded_512(char *fixed, int len, t_sha_words *words);
uint32_t			rightrotate(uint32_t input, uint32_t amount);
void				sha_process_chunk(char *chunk, t_sha_words *words);
void				sha_pad(t_ssl_input *input, void *words);
char				*flip(unsigned *padded, int len);

/*
** sha512 and sha384
*/

void				*ft_sha512(t_ssl_input *input);
void				*ft_sha384(t_ssl_input *input);
void				process_chunk_512(char *chunk, t_512_words *words);
int					read_sha_512(t_ssl_input *input, t_512_words *w);
void				split_padded_1024(char *fixed, int len, t_512_words *words);
//int					sha_pad_512(char *input, unsigned len, t_512_words *words);
void				sha_512_pad(t_ssl_input *input, void *words);
char				*flip_512(unsigned long *padded, int len);

/*
** base64
*/

void				*ft_base64(t_ssl_input *input);
void				ft_base64_e(t_ssl_input *input);
void				ft_base64_d(t_ssl_input *input);
int					read_base64_d(t_ssl_input *input);
void				verify_base64(char *s);
void				expand_base(unsigned chunk, unsigned char *e);
void				contract_base(unsigned chunk, unsigned char *d);
void				char_swap(unsigned char *chunk, int p);
int					minus_pad(char *input);

/*
** des
*/

void				*ft_des_cbc(t_ssl_input *input);
void				*ft_des_ecb(t_ssl_input *input);
void				ft_des_cbc_e(t_ssl_input *input);
void				ft_des_cbc_d(t_ssl_input *input);
void				ft_des_ecb_e(t_ssl_input *input);
void				ft_des_ecb_d(t_ssl_input *input);
void				gen_key(unsigned long key, unsigned long sub[16]);
unsigned			key_encrypt(unsigned right, unsigned long key);
unsigned long		init_perm(unsigned long block);
unsigned long		split_perm_e(unsigned long perm, unsigned long *key48);
unsigned long		split_perm_d(unsigned long perm, unsigned long *key48);
unsigned long		reverse_permute(unsigned left, unsigned right);
const int			***init_boxes(void);

#endif
