#include "printf.h"
#include "ft_ssl_md5.h"
#include "ssl_dispatch.h"

unsigned		flip_end(unsigned n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

unsigned long	flip_end_512(unsigned long n)
{
	return ((n >> 56) | ((n & 0xff000000000000) >> 40) |
			((n & 0xff0000000000) >> 24) | ((n & 0xff00000000) >> 8) |
			((n & 0xff000000) << 8) | ((n & 0xff0000) << 24) |
			((n & 0xff00) << 40) | (n << 56));
}

int				ssl_flags(char **av, int ac, int flags, int dis)
{
	if (!(flags & q))
	{
		if (flags & r)
		else
		{
			ft_printf("%s (%s)", av[1], av[ac - 1]);
			g_sslfuns[dis].hash(input, size);
		}
}

void			do_ssl(char **av, int ac, int flags, int dis)
{
	unsigned char	flags;
	int				i;

	i = 0;
	flags = 0;
	while (g_sslflags[i].flag && av[2][1] != g_sslflags[i].flag)
		i++;
	flags += g_sslflags[i].value;

}

int				main(int ac, char **av)
{
	int				dis;
	int				flags;
	
	dis = 0;
	if (ac == 3)
	{
		while (g_sslfuns[dis].name && ft_strcmp(av[1], g_sslfuns[dis].name))
			dis++;
		flags = ssl_flags(av, dis);
		do_ssl(av, ac, dis, flags);
	}
	return (0);
}
