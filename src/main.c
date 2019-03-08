#include "printf.h"
#include "ft_ssl_md5.h"

unsigned	flip_end(unsigned n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

void		force_print(char *string, int j)
{
	int i = -1;

	while (++i < j)
		printf("%hhu\n", string[i]);
}

int		main(int ac, char **av)
{
	if (ac == 2)
	{
		ft_sha256(av[1]);
		ft_putchar('\n');
	}
	return (0);
}
