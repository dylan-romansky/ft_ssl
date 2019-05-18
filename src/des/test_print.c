#include "ft_ssl.h"

void	print_bin(unsigned long num, int size)
{
	int				i;
	unsigned long	p;

	p = (unsigned long)1 << (size - 1);
	i = -1;
	while (++i < size)
	{
		if (!(i % 8) && i != 0)
			ft_printf(" ");
		ft_printf("%d", p & num ? 1 : 0);
		p >>= 1;
	}
	ft_printf("\n");
}
