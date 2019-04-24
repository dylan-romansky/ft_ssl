#include "ft_ssl_md5.h"

void		print_chunk(unsigned char *chunk, int i, int p)
{
	int		size;

	size = 4;
	while (size-- > p)
	{
		if (*chunk < 26)
			ft_printf("%c", 'A' + *chunk);
		else if (*chunk < 52)
			ft_printf("%c", 'a' + (*chunk - 26));
		else if (*chunk < 62)
			ft_printf("%c", '0' + (*chunk - 52));
		else if (*chunk < 64)
			ft_printf("%c", (*chunk - 62) ? '/' : '+');
		chunk++;
		i++;
	}
	write(1, "==", p);
}

unsigned	get_chunk(char *input, int i, int len, int size)
{
	unsigned		chunk;

	chunk = 0;
	if (i < (len - size - 1))
		ft_memcpy(&chunk, input + i, size);
	else 
		ft_memcpy(&chunk, input + i, len - i);
	return (chunk);
}

void		change_base(unsigned chunk, int decrypt, int i, int len)
{
	unsigned char	*d;
	int				p;

	d = decrypt ? contract_base(chunk) : expand_base(chunk);
	if (decrypt)
		decrypt_chunk(d, 3, i > len ? (i - len) : 0);
	else
		print_chunk(d, i, i > len ? (i - len) : 0);
	free(d);
}

int			ft_base64_e(char *input, size_t len)
{
	int		chunk;
	size_t	i;

	chunk = 0;
	i = 0;
	while (i < len)
	{
		chunk = get_chunk(input, i, len, i < len - 2 ? 3 : len - i);
		change_base(chunk, 0, i, len - 3);
		i += 3;
	}
	return (1);
}

int			ft_base64_d(char *input, size_t len)
{
	int		chunk;
	size_t	i;

	chunk = 0;
	i = 0;
	len -= minus_pad(input);
	while (i < len)
	{
		chunk = get_chunk(input, i, len, i < len - 3 ? 4 : len - i);
		change_base(chunk, 1, i, len - 4);
		i += 4;
	}
	return (1);
}
