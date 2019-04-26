#include "ft_ssl.h"

int		d(void)
{
	ft_printf("M butthole\nC 7A1FC80E72246434\nD ");
	t_ssl_input	*input;
	input = malloc(sizeof(t_ssl_input));
	char	*input2;
	unsigned long c = 0x7A1FC80E72246434;
	input2 = malloc(sizeof(char) * 8);
	input->input = ft_memcpy(input2, &c, 8);
	input->len = 8;
	input->key = 0x133457799BBCDFF1;
	input->outfd = 1;
	input->flags = 16;
	ft_des_ecb(input);
	return (0);
}

int		e(void)
{
	ft_printf("M butthole\nC 7A1FC80E72246434\nD ");
	t_ssl_input	*input;
	input = malloc(sizeof(t_ssl_input));
	input->input = "butthole";
	input->len = 8;
	input->key = 0x133457799BBCDFF1;
	input->outfd = 1;
	input->flags = 0;
	ft_des_ecb(input);
	return (0);
}

int		main(int ac, char **av)
{
	if (ac > 1)
		return (d());
	return (e());
}
