#include "libft.h"

void	print_chunk(char *chunk, int i, int p, int len)
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
		else if (size >= pad && *chunk)
			ft_printf("%c", (*chunk - 62) ? '/' : '+');
		else
			ft_printf("=");
	}
	if (!((i + p) % 64))
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
		if (i < len)
			chunk |= (int)input[i++];
	}
	return (chunk);
}

void	change_base(int chunk, int i, int crypt, int len)
{
	unsigned char	c;
	unsigned char	d[4];
	int				j;
	int				p;

	j = 4;
	p = 0;
	while (j--)
	{
		c = chunk & 63;
		if (i < len)
			d[i++] = crypt ? remove_chars(c) : c;
		else
			d[i + p++] = 0;
		chunk >>= 6;
	}
	if (crypt)
		print_chunk(d, i, len, p);
	else
		new_chunk(d);
}

void	ft_base64_e(char *input, size_t len)
{
	int		chunk;
	int		i;

	chunk = 0;
	i = 0;
	while (i < len + 3)
	{
		chunk = i < line ? get_chunk(data, i, len, 3) :
		change_base(chunk, i, 0, len);
		i += 3;
	}
	free(data);
}

void	ft_base64_d(char *input, size_t len)
{
	int		chunk;
	int		i;
	char	*filtered;

	chunk = 0;
	i = 0;
	filtered = filter_input(input);
	while (++i < len + 4)
	{
		chunk = get_chunk(input, i, len, 4);
		change_base(chunk, i, 1);
		i += 4;
	}
}
