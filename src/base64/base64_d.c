#include "ft_ssl_md5.h"

void			decrypt_chunk(unsigned char *d, int i, int p)
{
/*	int				i;
	int				garbage;
	int				chunk;

	i = 4;
	chunk = 0;
	garbage = 0;
	while (--i >= 0)
	{
		chunk <<= 6;
		if (d[i] == 255)
			garbage++;
		else
			chunk |= d[i];
	}
	print_decrypt(chunk, 3 - garbage);*/
	write(1, d, i - p);
}

unsigned char	char_base(char c)
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

unsigned		remove_chars(unsigned chunk)
{
	char	d[4];
	int		i;

	i = -1;
	ft_memcpy(d, &chunk, 4);
	while (++i < 4)
		d[i] = char_base(d[i]);
	ft_memcpy(&chunk, d, 4);
	return (chunk);
}

unsigned		expand_base(unsigned chunk)
{
	unsigned	expanded;
	int			i;
	int			j;

	expanded = 0;
	i = -1;
	j = 0;
	ft_printf("%32b\n", chunk);
	while (++i < 32)
	{
		expanded += (1 << i) & chunk ? 1 << j : 0;
		j++;
		if (!((i + 1) % 6))
			j += 2;
	}
	ft_printf("%32b\n", expanded);
	return(expanded);
}

unsigned		contract_base(unsigned chunk)
{
	unsigned	contracted;
	int			i;
	int			j;

	chunk = remove_chars(chunk);
	contracted = 0;
	i = -1;
	j = 0;
	while (++i < 32)
	{
		contracted += (1 << i) & chunk ? 1 << j++: 0;
		if (!((j + 1) % 6))
			i += 2;
	}
	return(contracted);
}
