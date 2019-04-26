#include "ft_ssl.h"

void	ft_des_ecb_e(t_ssl_input *input)
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
		chunk = split_perm(chunk);
		write(input->outfd, &chunk, 8); //make sure this outputs the way you want
		i += 8;
	}
}

/*
** write decoding functions, should be simple since in theory you just apply the
** keys in the opposite order
*/
