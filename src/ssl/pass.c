/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:23:13 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/13 07:15:00 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

unsigned long	*write_pass_hash(t_md5_words *words, unsigned long *salt_hash)
{
	salt_hash[0] = flip_end(words->a0);
	salt_hash[0] <<= 32;
	salt_hash[0] |= flip_end(words->b0);
	salt_hash[1] = flip_end(words->c0);
	salt_hash[1] <<= 32;
	salt_hash[1] |= flip_end(words->d0);
	free(words);
	return (salt_hash);
}

unsigned long	*split_input_salt(char *input, int len, t_md5_words *word, unsigned long *hashed)
{
	char			process[64];
	int				i;
	int				j;

	j = 0;
	while (j < len)
	{
		i = 0;
		while (i < 64)
			process[i++] = input[j++];
		split_input_32(process, word);
	}
	return (write_pass_hash(word, hashed));
}

unsigned long	*salt_md5(char *input, size_t len, unsigned long *hashed)
{
	size_t			flen;
	size_t			i;
	t_md5_words		*words;

	words = (t_md5_words *)malloc(sizeof(t_md5_words));
	words->a0 = 0x67452301;
	words->b0 = 0xefcdab89;
	words->c0 = 0x98badcfe;
	words->d0 = 0x10325476;
	i = 1 + len;
	while ((i + 8) % 64)
		i++;
	input[len] = (unsigned char)128;
	flen = len * 8;
	ft_memcpy(input + i, &flen, 8);
	split_input_salt(input, i + 8, words, hashed);
	return (hashed);
}

/*
** adapt this later to handle passwords longer than BUFF_LEN
*/

unsigned long	salt_pass(t_ssl_input *input, char *tmp, unsigned long salt)
{
	size_t			size;
	unsigned long	salted[2];
	unsigned long	ret;

	ft_printf("it salty %llx\n", salt);
	size = ft_strlen(tmp);
	ft_memcpy(input->input, tmp, size);
	ft_memcpy(input->input + size, &salt, 8);
	if (!salt_md5(input->input, size + 8, salted))
	{
		ft_printf("Error: failed to create key\n");
		exit(1);
	}
	if (!input->iv)
		input->iv = salted[1];
	ret = salted[0];
	ft_bzero(salted, 2 * sizeof(unsigned long));
	return (ret);
}

void			pass_input(t_ssl_input *input)
{
	if (!input->pass)
		input->pass = getpass("enter des encryption password: ");
	if (!input->salt && !(input->flags & s2))
		getentropy(&(input->salt), 8);
	input->flags |= (s2 | p);
	input->key = salt_pass(input, input->pass, input->salt);
}
