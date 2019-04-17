#include "libft.h"

unsigned		flip_end(unsigned n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

int main(void)
{
	char test[4];
	int chunk;

	ft_memcpy(&chunk, "fuck", 4);
	ft_memcpy(test, &chunk, 4);
	write(1, test, 4);
	return (0);
}
