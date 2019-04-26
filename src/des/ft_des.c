#include "ft_ssl.h"

void	des_pad(t_ssl_input *input)
{
	unsigned char	*pad;
	unsigned int	val;
	int				i;

	i = 0;
	val = 8 - (input->len % 8);
	pad = (unsigned char *)ft_strnew(input->len + val);
	ft_memcpy(pad, input->input, input->len);
	while (i < val)
		pad[i++ + input->len] = val;
	free(input->input);
	input->input = pad;
	input->len += val;
}

int		ft_des_ecb(t_ssl_input *input)
{
	if (len % 8 && input->flags & e)
		des_pad(input);
	if (input->flags & e)
		ft_des_ecb_e(input);
	else
		ft_des_ecb_d(input);
}

int		ft_des_cbc(t_ssl_input *input)
{
	if (len % 8 && input->flags & e)
		des_pad(input);
	if (input->flags & e)
		ft_des_cbc_e(input);
	else
		ft_des_cbc_d(input);
	return (0);
}
