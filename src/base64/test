#include "ft_ssl.h"

unsigned		flip_end(unsigned n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
		((n & 0xff00) << 8) | (n << 24));
}

int main(void)
{
	char *s1 = "butt";
	char *s2 = "dGVzdCB0ZXN0IHRlc3QgdGVzdCB0ZXN0IHRlc3QgdGVzdCB0ZXN0IHRlc3QgdGVzdHRlc3QgdGVzdCB0ZXN0IHRlc3QgdGVzdCB0ZXN0IHRlc3QgdGVzdCB0ZXN0IHRlc3QK";
	ft_base64_e(s1, ft_strlen(s1));
	ft_printf("\n");
	ft_base64_d(s2, ft_strlen(s2));
	return (0);
}
