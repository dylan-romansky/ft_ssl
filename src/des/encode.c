#include "ft_ssl.h"
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

const int	block_perm_k [] = {
	16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18,
	31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22,
	11, 4, 25};

unsigned		permute_box(unsigned box)
{
	int				i;
	unsigned		perm;

	i = -1;
	perm = 0;
	while (++i < 32)
	{
		perm <<= 1;
		perm |= (1 << (32 - block_perm_k[i])) & box ? 1 : 0;
	}
	return (perm);
}

unsigned		s_boxing(unsigned long expand, int i)
{
	unsigned char	block;
	unsigned char	row;
	unsigned char	column;

	if (i == -1)
		return (0);
	block = expand & 63;
	expand >>= 6;
	row = ((block >> 4) & 2) + (1 & block);
	column = (block >> 1) & 15;
	return (boxes_k[i][row][column] | (s_boxing(expand, i - 1) << 4));
}

/*
** issue is somewhere in here. I imagine it has to do with either which one is
** being shifted or the way I'm indexing my arrays
*/ 
unsigned		key_encrypt(unsigned right, unsigned long key)
{
	unsigned long	expand;
	int				i;

	expand = 0;
	i = -1;
	while (++i < 48)
	{
		expand <<= 1;
		expand |= ((unsigned long)1 << (32 - expansion_k[i])) & right ? 1 : 0;
	}
	return (permute_box(s_boxing(expand ^ key, 7)));
}

/*
** initial permutation of data block. verified this works.
*/

unsigned long	init_perm(unsigned long block)
{
	unsigned long	perm;
	int				i;

	i = -1;
	perm = 0;
	while (++i < 64)
	{
		perm <<= 1;
		perm |= ((unsigned long)1 << (64 - init_perm_k[i])) & block ? 1 : 0;
	}
	return (perm);
}

