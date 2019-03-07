#include "printf.h"
#include "ft_ssl_md5.h"

int		main(int ac, char **av)
{
	if (ac == 2)
	{
		ft_md5(av[1]);
		ft_putchar('\n');
	}
	return (0);
}
