#include "ft_ssl_md5.h"

void			print_decrypt(int chunk, int i)
{
	char			decrypted[3];

	chunk = flip_end(chunk);
	ft_memcpy(decrypted, &chunk, 3);
	write(1, decrypted, i);
}

void			decrypt_chunk(unsigned char *d)
{
	int				i;
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
	print_decrypt(chunk, 3 - garbage);
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
	return (255);
}
