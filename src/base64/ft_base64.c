#include "ft_ssl_md5.h"

/*
** potential bug in encoding, might be working from the wrong end,
** could also be completely misguided in my data storage and conversion.
** try pulling out front 6, then shifting over 2. Or shift the 2 before
** pulling the 6.
*/

void	print_chunk(unsigned char *chunk, int i, int p)
{
	int size;

	size = 4;
	while (size-- >= 0)
	{
		if (*chunk < 26)
			ft_printf("%c", 'A' + *chunk);
		else if (*chunk < 52)
			ft_printf("%c", 'a' + (*chunk - 26));
		else if (*chunk < 62)
			ft_printf("%c", '0' + (*chunk - 52));
		else if (*chunk < 64)
			ft_printf("%c", (*chunk - 62) ? '/' : '+');
		else
			ft_printf("=");
		chunk++;
	}
//	if (i > !((i + p) % 64))
//		ft_printf("\n");
}

int		get_chunk(char *input, int i, int len, int size)
{
	int				chunk;

	chunk = 0;
	if (i < len)
		ft_memcpy(&chunk, input, size);
	else 
		ft_memcpy(&chunk, input, size - (i - len));
	flip_end(chunk);
	if (i > len)
		chunk >>= 8 * (i - len);
	return (chunk);
}

/*void	change_base(unsigned chunk, int i, int decrypt, int len)
{
	unsigned char	c;
	unsigned char	d[4];
	int				j;
	int				p;

	j = decrypt ? 3 : 2;
	p = i > len ? i - len : 0;
	ft_printf("%b\n", chunk);
	while (j >= 0)
	{
		c = chunk & 63;
		if (i + j < len)
		{
			printf("encoding %d\n\n", c);
			d[j] = decrypt ? remove_chars(c) : c;
		}
		chunk >>= decrypt ? 8 : 6;
		j--;
	}
	int q = -1;
	while (++q < 4)
		ft_printf("%d\n", d[q]);
	if (decrypt)
		decrypt_chunk(d);
	else
		print_chunk(d, i, p);
}*/
void	change_base(unsigned chunk, int decrypt, int i, int len)
{
	unsigned char	d[4];
	int				p;

	p = decrypt ? contract_base(chunk) : expand_base(chunk);
	ft_memcpy(d, &p, decrypt ? 3 : 4);
	if (decrypt)
		decrypt_chunk(d, i, i > len ? i - len : 0);
	else
		print_chunk(d, i, i > len ? i - len : 0);
}

int		ft_base64_e(char *input, size_t len)
{
	int		chunk;
	size_t	i;

	chunk = 0;
	i = 0;
	while (i < len + 2)
	{
		chunk = get_chunk(input, i, len, 3);
		chunk >>= 1;
		change_base(chunk, i, 0, len);
		i += 3;
	}
	return (1);
}

int		ft_base64_d(char *input, size_t len)
{
	int		chunk;
	size_t	i;

	chunk = 0;
	i = 0;
	while (++i < len + (size_t)3)
	{
		chunk = get_chunk(input, i, len, 4);
		change_base(chunk, i, 1, len);
		i += 4;
	}
	return (1);
}
