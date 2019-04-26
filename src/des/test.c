#include "ft_ssl.h"

int		main(void)
{
	ft_printf("M 0123456789ABCDEF\nC 85E813540F0AB405\nD ");
	t_ssl_input	*input;
	input = (t_ssl_input *)malloc(sizeof(t_ssl_input));
	unsigned long	message = 0x85E813540F0AB405;
	char			*input1 = malloc(sizeof(char) * 8);
	input->input = ft_memcpy(input1, &message, 8);
	input->len = 8;
	input->key = 0x133457799BBCDFF1;
	input->outfd = 1;
	input->flags = 16;
	ft_des_ecb(input);
	return (0);
}
