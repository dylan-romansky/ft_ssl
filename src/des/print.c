#include "stdio.h"
#include "ft_ssl.h"

int	main(void)
{
	int fd = open("test", O_RDONLY);
	char buf[40];
	int ret = read(fd, buf, 39);
	buf[ret] = 0;
	unsigned long	hex;
	hex = 0;

	ft_memcpy(&hex, buf, ret);
	printf("%lX\n", hex);
	return (0);
}
