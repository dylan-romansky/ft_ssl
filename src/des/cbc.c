#include "ft_ssl.h"

int	ft_des_cbc_e(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	vector;
	unsigned long	*subkeys;
	int				i;

	i= 0;
	subkeys = gen_key(input->key);
	vector = input->iv;
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk ^= vector;
		chunk = init_perm(chunk);
		chunk = split_perm_e(chunk, subkeys);
		ft_dprintf(input->outfd, "%16llX\n", chunk);
		vector = chunk;
		i += 8;
	}
	return (0);
}

int	ft_des_cbc_d(t_ssl_input *input)
{
	unsigned long	chunk;
	unsigned long	vector;
	unsigned long	*subkeys;
	int				i;

	i= 0;
	subkeys = gen_key(input->key);
	vector = input->iv;
	while (i < input->len)
	{
		chunk = 0;
		ft_memcpy(&chunk, input->input + i, 8);
		chunk ^= vector;
		chunk = init_perm(chunk);
		chunk = split_perm_d(chunk, subkeys);
		ft_dprintf(input->outfd, "%16llX\n", chunk);
		vector = chunk;
		i += 8;
	}
	return (0);
}
