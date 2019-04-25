#include "ssl_md5_s_boxes.h"

const int	init_perm_k [] = {
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36,
	28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33,
	25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61,
	53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31,
	23, 15, 7};

const int	expansion_k [] = {
	32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10,
	11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18,
	19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26,
	27, 28, 29, 28, 29, 30, 31, 32, 1};

/*
** this relies on my being able to index static arrays the way I want
*/

unsigned		s_boxing(unsigned long expand, int i)
{
	char	block;
	char	row;
	char	column;

	block = expand & 63;
	expand >>= 6;
	row = ((block >> 4) & 2) + (1 & block);
	column = (block >> 1) & 15;
	if (!g_boxes[i].box)
		return (0);
	return ((s_boxing(expand, i + 1) << 4) | g_boxes[i].box[row][column]);
}

unsigned		permute_box(unsigned box)
{
	int				i;
	unsigned		perm;

	i = 32;
	perm = 0;
	while (--i >= 0)
	{
		perm <<= 1;
		perm |= (1 << (block_perm_k[i] - 1)) & box ? 1 : 0;
	}
	return (perm);
}

unsigned		key_encrypt(unsigned right, unsigned long key)
{
	unsigned long	expand;
	int				i;

	expand = 0;
	i = 48;
	while (--i >= 0)
	{
		expand <<= 1;
		expand |= (1 << (init_perm_k[i] - 1)) & right ? 1 : 0;
	}
	return (permute_box(s_boxing(expand ^ key, 0)));
}

unsigned long	init_perm(unsigned long block)
{
	unsigned long	perm;
	int				i;

	i = 64;
	perm = 0;
	while (--i >= 0)
	{
		perm <<= 1;
		perm |= (1 << init_perm_k[i]) & block ? 1 : 0;
	}
	return (perm);
}
/*
** consider adding data type for left and right tables
*/

void			split_perm(unsigned long perm, unsigned long *key48)
{
	unsigned		left[17];
	unsigned		right[17];
	int				i;

	left[0] = perm >> 32;
	right[0] = perm & 0xffffffff;
	i = 0;
	while (++i < 17)
	{
		left[i] = right[i - 1];
		right[i] = left[i - 1] ^ key_encrypt(right[i - 1], key48[i - 1]);
	}
}
