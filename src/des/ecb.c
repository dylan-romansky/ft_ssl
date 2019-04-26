#include "ft_ssl.h"

int	ft_des_ecb_e(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	*subkeys;
	int				i;

	i = 0;
	subkeys = gen_key(input->key);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = init_perm(chunk);
		chunk = split_perm_e(chunk, subkeys);
		ft_dprintf(input->outfd, "%16llX", chunk);
		i += 8;
	}
	return (0);
}

/*
** write decoding functions, should be simple since in theory you just apply the
** keys in the opposite order, so verify that is in fact what you are doing
*/

int	ft_des_ecb_d(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	*subkeys;
	int				i;

	i = 0;
	subkeys = gen_key(input->key);
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk = init_perm(chunk);
		chunk = split_perm_d(chunk, subkeys);
		write(input->outfd, &chunk, 8);//write ternary to decide final write length
		i += 8;
	}
	return (0);
}
