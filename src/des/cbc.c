#include "ft_ssl.h"

void	ft_des_cbc_e(t_ssl_input *input)
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
		chunk = split_perm(chunk);
		write(input->outfd, &chunk, 8);
		vector = chunk;
		i += 8;
	}
}
