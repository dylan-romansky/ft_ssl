#include "libft.h"

/*
** decrypt might be fucked up
*/

void	print_chunk(char *chunk, int i)
{
	int size;

	size = 4;
	while (size--)
	{
		if (*chunk < 26)
			ft_printf("%c", 'A' + *chunk);
		else if (*chunk < 52)
			ft_printf("%c", 'a' + (*chunk - 26));
		else if (*chunk < 62)
			ft_printf("%c", '0' + (*chunk - 52));
		else
			ft_printf("%c", (*chunk - 62) ? '/' : '+');
	}
	if (!(i % 64))
		ft_printf("\n");
}

int		get_chunk(char *input, int i, int len, int size)
{
	int		chunk;
	int		count;

	chunk = 0;
	count = 0;
	while (count++ < size)
	{
		chunk <<= 8;
		chunk |= (int)input[i];
	}
	return (chunk);
}

void	change_base(int chunk, int i, int crypt)
{
	unsigned char	c;
	unsigned char	d[4];
	int				i;

	i = 4;
	while (i--)
	{
		c = chunk & 63;
		d[i] = crypt ? remove_chars(c) : c;
		chunk >>= 6;
	}
	if (crypt)
		print_chunk(d, i);
	else
		new_chunk(d);
}

void	ft_base64_e(char *input, size_t len)
{
	int		chunk;
	int		i;
	char	*data;

	chunk = 0;
	i = 0;
	data = padding(input, len);
	while (i < len + 3)
	{
		chunk = get_chunk(data, i, len, 3);
		change_base(chunk, i, 0);
		i += 3;
	}
	free(data);
}

void	ft_base64_d(char *input, size_t len)
{
	int		chunk;
	int		i;

	chunk = 0;
	i = 0;
	while (++i < len + 4)
	{
		chunk = get_chunk(input, i, len, 4);
		change_base(chunk, i, 1);
		i += 4;
	}
}
