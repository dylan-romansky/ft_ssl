/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 02:29:52 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/22 17:00:35 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ssl_md5_enums.h"

/*
** will need to verify if this works with binary files
*/

void			print_md5(t_md5_words *words)
{
	words->a0 = flip_end(words->a0);
	words->b0 = flip_end(words->b0);
	words->c0 = flip_end(words->c0);
	words->d0 = flip_end(words->d0);
	ft_printf("%08x%08x%08x%08x", words->a0, words->b0, words->c0, words->d0);
}

void			split_input_32(char *chunk, t_md5_words *word)
{
	unsigned		chunks[16];
	int				i;
	int				j;
	int				num;

	i = 0;
	j = 0;
	while (j < 64)
	{
		ft_memcpy(&num, chunk + j, 4);
		chunks[i++] = num;
		j += 4;
	}
	i = -1;
	word->a = word->a0;
	word->b = word->b0;
	word->c = word->c0;
	word->d = word->d0;
	while (++i < 64)
		hashing_functions_md5(word, i, chunks);
	word->a0 += word->a;
	word->b0 += word->b;
	word->c0 += word->c;
	word->d0 += word->d;
}

void			split_input_512(char *input, int len, t_md5_words *word)
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
}

int				read_md5(t_ssl_input *input, t_md5_words *w)
{
	size_t	pad;
	size_t flen;

	ft_bzero(input->input, BUFF_SIZE);
	input->read = 0;
	if (!(input->flags & s))
		input->read = read(input->infd, input->input, BUFF_SIZE);
	if (input->read <= 0)
		return (0);
	input->len += input->read;
	if (input->flags & p && input->infd == 0)
		write(input->outfd, input->input, input->read);
	if (input->read < BUFF_SIZE || input->flags & s)
	{
		if (input->read + 1 > BUFF_SIZE - 8)
		{
			split_input_512(input->input, 64, w);
			input->read -= 64;
			ft_memcpy(input->input, input->input + 64, input->read);
		}
		pad = (size_t)(input->read + 1);
		while ((pad + 8) % 64)
			input->input[pad++] = 0;
		input->input[input->read] = (unsigned char)128;
		flen = input->len * 8;
		ft_memcpy(input->input + pad, &flen, 8); //this may be incorrect so I'm leaving the old adaption below
		input->read = pad + 8;
	}
	return (1);
}

int				ft_md5(t_ssl_input *input)
{
//	int				flen;
//	size_t			i;
//	char			*fixed;
	t_md5_words		*words;

	words = (t_md5_words *)malloc(sizeof(t_md5_words));
	words->a0 = 0x67452301;
	words->b0 = 0xefcdab89;
	words->c0 = 0x98badcfe;
	words->d0 = 0x10325476;
/*	i = 1 + input->len;
	while ((i + 8) % 64)
		i++;
	if (!(fixed = ft_strnew(i + 8)))
		return (-1);
	fixed = ft_memcpy(fixed, input->input, input->len);
	fixed[input->len] = (unsigned char)128;
	flen = (int)(input->len * 8);
	ft_memcpy(fixed + i, &flen, 4);*/
	while (read_md5(input, words))
		split_input_512(input->input, input->read, words);
	ft_bzero(input->input, BUFF_SIZE);
	print_md5(words);
	free(words);
//	free(fixed);
	return (0);
}

/*
 * read up to BUFF_SIZE and drop them chunks through md5
 * as soon as a read is less than BUFF_SIZE do the padding
 * - make sure there's consistently enough room to pad
 *   - maybe make the padding be a string?
 *   - or run a few chunks through to make sure there's room
 * then run those chunks through the algo as usual
*/
