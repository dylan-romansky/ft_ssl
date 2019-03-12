#include "ft_ssl_md5.h"

void	flag_error(char *name)
{
	ft_printf("ft_ssl_md5: %s: invalid flags\n", name);
	exit (1);//verify this is allowed
}

void	error_nodis(void)
{
	ft_printf("ft_ssl_md5: no algorithm specified\n");
	exit (1);
}
