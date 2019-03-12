#include "ft_ssl_md5.h"

void	flag_error(char *name, char flag)
{
	ft_printf("%s: illegal option -- %c\n", name, flag);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]\n", name);
	exit (1);
}

void	error_nodis(char *input)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\nStandard");
	ft_printf("commands:\n\nMessage Digest commands:\nmd5\nsha224\nsha256\n");
	ft_printf("sha384\nsha512\n\nCipher commands:\n", input);
	exit (1);
}
