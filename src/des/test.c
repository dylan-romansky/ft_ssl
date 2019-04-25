#include "ft_ssl.h"

int		main(void)
{
	unsigned long	message = 0x0123456789ABCDEF;
	unsigned long	key = 0x133457799BBCDFF1;
	unsigned long	*subkeys = gen_key(key);
	ft_printf("good\n");
	unsigned long permuted = init_perm(message);
	ft_printf("%llb\n", permuted);
	ft_printf("%llX\n", split_perm(permuted, subkeys));
	return (0);
}
