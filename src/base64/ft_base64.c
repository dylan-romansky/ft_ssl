#include "libft.h"

void	print_chunk(char *chunk, int size, int i)
{
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

void	change_base(int chunk, int size, int i)
{
	char	c;
	char	d[4];
	int		i;

	i = size
	while (i--)
	{
		c = 0;
		c |= chunk;
		d[i] = c;
		chunk >>= 8;
	}
	print_chunk(d, size, i);
}

void	ft_base64_e(char *input, size_t len)
{
	int		chunk;
	int		i;

	chunk = 0;
	i = 0;
	while (i < len + 4)
	{
		chunk = get_chunk(input, i, len, 4);
		change_base(chunk, 3, i);
		i += 4;
	}
}

void	ft_base64_d(char *input, size_t len)
{
	int		chunk;
	int		i;

	chunk = 0;
	i = 0;
	while (++i < len + 3)
	{
		chunk = get_chunk(input, i, len, 3);
		change_base(chunk, 4, i);
		i += 3;
	}
}
