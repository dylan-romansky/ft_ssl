#include "ft_ssl.h"

int		main(void)
{
	unsigned long	key = 0x133457799BBCDFF1;
	ft_printf("key  %64llb\n", key);
	const unsigned long	*subkeys = gen_key(key);

	int i = -1;
//	while (++i < 16)
//		ft_printf("%-5d%64llb\n", i + 1, subkeys[i]);
	return (0);
}
