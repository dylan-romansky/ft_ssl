/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 01:55:56 by dromansk          #+#    #+#             */
/*   Updated: 2019/02/28 17:13:55 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	ft_not(unsigned char bits)
{
	unsigned char	ret;
	short			b;

	b = 256;
	ret = 0;
	while (b && !(b & bits))
		b >>= 1;
	while (b)
	{
		if (!(b & bits))
			ret |= 1;
		if (b != 1)
			ret <<= 1;
		b >>= 1;
	}
	return (ret);
}

unsigned char	b_or(unsigned char b, unsigned char c, unsigned char d)
{
	return((b & c) | (ft_not(b) & d));
}

unsigned char	d_or(unsigned char b, unsigned char c, unsigned char d)
{
	return((b & d) | (c & ft_not(d)));
}

unsigned char	bcd_xor(unsigned char b, unsigned char c, unsigned char d)
{
	return(b ^ c ^ d);
}

unsigned char	c_xor_b_or_nd(unsigned char b, unsigned char c, unsigned char d)
{
	return(c ^ (b | ft_not(d)));
}
