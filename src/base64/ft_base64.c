#include "ft_ssl_md5.h"
/*
** make base change shove chunk over differently depending on how many chunks it needs to get
** possibly scratch that as ints store their numbers backwards so chars need to be flipped
*/

void	print_chunk(unsigned char *chunk, int i, int p)
{
	int size;

	size = 5;
	while (size--)
	{
		if (*chunk < 26)
			ft_printf("%c", 'A' + *chunk);
		else if (*chunk < 52)
			ft_printf("%c", 'a' + (*chunk - 26));
		else if (*chunk < 62)
			ft_printf("%c", '0' + (*chunk - 52));
		else if (size >= p && *chunk)
			ft_printf("%c", (*chunk - 62) ? '/' : '+');
		else
			ft_printf("=");
	}
	if (!((i + p) % 64))
		ft_printf("\n");
}

int		get_chunk(char *input, int i, int len, int size)
{
	int				chunk;

	chunk = 0;
	if (i < len)
		ft_memcpy(&chunk, input, size);
	else 
		ft_memcpy(&chunk, input, size - (i - len));
	return (chunk);
}

void	change_base(int chunk, int i, int crypt, int len)
{
	unsigned char	c;
	unsigned char	d[4];
	int				j;
	int				p;
	int				k;

	j = crypt ? 3 : 4;
	k = 0;
	p = 0;
	while (j - p)
	{
		c = chunk & 63;
		if (i + j < len)
		{
			j--;
			d[k++] = crypt ? remove_chars(c) : c;
		}
		else
			p++;
		chunk >>= crypt ? 8 : 6;
	}
	if (crypt)
		print_chunk(d, i, p);
	else
		decrypt_chunk(d);
}

int		ft_base64_e(char *input, size_t len)
{
	int		chunk;
	size_t	i;

	chunk = 0;
	i = 0;
	while (i < len + 3)
	{
		chunk = get_chunk(input, i, len, 3);
		change_base(chunk, i, 1, len);
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
	while (++i < len + (size_t)4)
	{
		chunk = get_chunk(input, i, len, 4);
		change_base(chunk, i, 0, len);
		i += 4;
	}
	return (1);
}
