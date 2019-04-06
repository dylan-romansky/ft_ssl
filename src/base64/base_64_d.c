#include "ft_ssl_md5.h"

void			print_decrypt(int chunk)
{
	char			d[3];
	int				i;

	i = 4;
	while (i--)
	{
		d[i] = chunk & 127;
		chunk  >>= 8;
	}
	write(1, d, 3);
}

void			new_chunk(char *d)
{
	int				i;
	int				chunk;

	i = -1;
	while (++i < 4)
	{
		chunk |= d[i];
		chunk <<= 6;
	}
	print_decrypt(chunk);
}

unsigned char	remove_chars(char c)
{
	if ('A' <= c && c <= 'Z')
		return (c - 'A');
	if ('a' <= c && c <= 'z')
		return (c - 'a' + 26);
	if (0 <= c && c <= '9')
		return (c - '0' + 52);
	if (c == '+')
		return (62);
	if (c == '/')
		return (63);
	return (0);
}

char			*filter_input(char *input)
{
	int		i;
	char	*filtered;

	i = chr_index(input, '=');
	if (input[i] == '=')
		filtered = ft_strndup(input, i);
}
