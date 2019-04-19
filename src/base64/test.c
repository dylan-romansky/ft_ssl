#include "ft_ssl_md5.h"

unsigned		flip_end(unsigned n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

int main(void)
{
	ft_base64_e("butt", 4);
	return (0);
}
