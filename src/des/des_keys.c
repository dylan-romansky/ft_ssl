const int keygen56_k[] = {
	57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26,
	18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52,
	44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46,
	38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5,
	28, 20, 12, 4};

uint32_t	rightrotate(uint32_t input, uint32_t amount)
{
	return ((((unsigned int)input >> amount)) |
			(0x0fffffff & (input << (28 - amount))));
}

const unsigned long(unsigned long key)
{
	unsigned long	key56;
	int				i;

	key56 = 0;
	i = 0;
	while (i < 56)
		key = (1 << keygen56_k[i++]) | key;
	return (key);
}
