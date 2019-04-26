#include "ft_ssl.h"

int		main(void)
{
	unsigned long	message = 0x0123456789ABCDEF;
	unsigned long	key = 0x133457799BBCDFF1;
	unsigned long	*subkeys = gen_key(key);
	unsigned long permuted = init_perm(message);
	ft_printf("result    %llX\n", split_perm(permuted, subkeys));
	ft_printf("expecting 85E813540F0AB405\n");
	return (0);
}
