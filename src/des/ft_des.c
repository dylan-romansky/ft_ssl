#include "ft_ssl.h"
#include "ssl_md5_enums.h"

/*
** unpadding can check the value of last byte and see if the preceeding x bytes are the same number
*/

void	des_pad(t_ssl_input *input)
{
	unsigned char	*pad;
	unsigned int	val;
	unsigned		i;

	i = 0;
	val = 8 - (input->len % 8);
	pad = (unsigned char *)ft_strnew(input->len + val);
	ft_memcpy(pad, input->input, input->len);
	while (i < val)
		pad[i++ + input->len] = val;
	free(input->input);
	input->input = (char *)pad;
	input->len += val;
}

int		ft_des_ecb(t_ssl_input *input)
{
	if (input->len % 8 && !(input->flags & d))
		des_pad(input);
	if (input->flags & d)
		ft_des_ecb_d(input);
	else
		ft_des_ecb_e(input);
	return (0);
}

int		ft_des_cbc(t_ssl_input *input)
{
	if (input->len % 8 && !(input->flags & d))
		des_pad(input);
	if (input->flags & d)
		ft_des_cbc_d(input);
	else
		ft_des_cbc_e(input);
	return (0);
}
