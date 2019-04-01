#include "libft.h"

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

void	print_chunk(int chunk, int size)
{
	int		c;
	int		point;

	c = 0;
	point = ;
	point <<= 8 * size;
	while (size--)
}

int		ft_base64_e(char *input, size_t len)
{
	int		chunk;
	int		i;

	chunk = 0;
	i = 0;
	while (i < len + 4)
	{
		chunk = get_chunk(input, i, len, 4);
		print_chunk(chunk, 3);
		i += 4;
	}
}

int		ft_base64_d(char *input, size_t len)
{
	int		chunk;
	int		i;

	chunk = 0;
	i = 0;
	while (++i < len + 3)
	{
		chunk = get_chunk(input, i, len, 3);
		print_chunk(chunk, 4);
		i += 3;
	}
}
