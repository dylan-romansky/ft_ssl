/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:23:13 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/18 06:43:25 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
/*
unsigned long	*write_pass_hash(t_md5_words *words)
{
	unsigned long	*salt_hash;

	salt_hash = (unsigned long *)malloc(sizeof(unsigned long) * 2);
	salt_hash[0] = flip_end(words->a0);
	salt_hash[0] <<= 32;
	salt_hash[0] |= flip_end(words->b0);
	salt_hash[1] = flip_end(words->c0);
	salt_hash[1] <<= 32;
	salt_hash[1] |= flip_end(words->d0);
	free(words);
	return (salt_hash);
}

unsigned long	*split_input_salt(char *input, int len, t_md5_words *word)
{
	char			*process;
	int				i;
	int				j;

	process = NULL;
	j = 0;
	while (j < len)
	{
		i = 0;
		process = ft_strnew(64);
		while (i < 64)
			process[i++] = input[j++];
		split_input_32(process, word);
		free(process);
	}
	return (write_pass_hash(word));
}

unsigned long	*salt_md5(char *input, size_t len)
{
	int				flen;
	size_t			i;
	char			*fixed;
	t_md5_words		*words;
	unsigned long	*hashed;

	words = (t_md5_words *)malloc(sizeof(t_md5_words));
	words->a0 = 0x67452301;
	words->b0 = 0xefcdab89;
	words->c0 = 0x98badcfe;
	words->d0 = 0x10325476;
	i = 1 + len;
	while ((i + 8) % 64)
		i++;
	if (!(fixed = ft_strnew(i + 8)))
		return (NULL);
	fixed = ft_memcpy(fixed, input, len);
	fixed[len] = (unsigned char)128;
	flen = (int)(len * 8);
	ft_memcpy(fixed + i, &flen, 4);
	hashed = split_input_salt(fixed, i + 8, words);
	free(fixed);
	return (hashed);
}

unsigned long	salt_pass(t_ssl_input *input, char *tmp, char *salt)
{
	char			*mix;
	size_t			size;
	unsigned long	*salted;
	unsigned long	ret;

	size = ft_strlen(tmp);
	mix = ft_strnew(size + 8);
	ft_memcpy(mix, tmp, size);
	ft_memcpy(mix + size, salt, 8);
	if (!(salted = salt_md5(mix, size + 8)))
	{
		ft_printf("Error: failed to create key\n");
		exit(1);
	}
	free(mix);
	if (!input->iv)
		input->iv = salted[1];
	ret = *salted;
	free(salted);
	free(salt);
	return (ret);
}
*/
unsigned long	*salt_sha256(t_ssl_input *input)
{
		t_sha_words		*words;

			words = (t_sha_words *)malloc(sizeof(t_sha_words));
			words->h0 = 0x6a09e667;
			words->h1 = 0xbb67ae85;
			words->h2 = 0x3c6ef372;
			words->h3 = 0xa54ff53a;
			words->h4 = 0x510e527f;
			words->h5 = 0x9b05688c;
			words->h6 = 0x1f83d9ab;
			words->h7 = 0x5be0cd19;
			if (sha_pad(input->input, (unsigned)(input->len), words) < 0)
			{
				free(words);
				return (-1);
			}

unsigned long	salt_pass(t_ssl_input *input, char *tmp, char *salt)
{
	char			*mix;
	size_t			size;
	unsigned long	*salted;
	unsigned long	ret;

	size = ft_strlen(tmp);
	mix = ft_strnew(size + 8);
	ft_memcpy(mix, tmp, size);
	ft_memcpy(mix + size, salt, 8);
	if (!(salted = salt_sha256(mix, size + 8)))
	{
		ft_printf("Error: failed to create key\n");
		exit(1);
	}
	free(mix);
	if (!input->iv)
		input->iv = salted[1];
	ret = *salted;
	free(salted);
	free(salt);
	return (ret);
}

void			pass_input(t_ssl_input *input)
{
	char			*tmp;
	unsigned long	salt;

	tmp = getpass("enter des encryption password: ");
	salt = gen_salt();
	input->key = salt_pass(input, tmp, ft_ltoa_base(salt, 16));
}
