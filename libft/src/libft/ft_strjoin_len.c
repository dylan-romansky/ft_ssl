/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 15:52:27 by dromansk          #+#    #+#             */
/*   Updated: 2019/01/11 16:08:06 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_len(char const *s1, char const *s2, size_t len1,
		size_t len2)
{
	char	*n;
	int		i;

	i = -1;
	if (!s1 || !s2 || !(n = ft_strnew(len1 + len2)))
		return (NULL);
	while ((size_t)++i < len1)
		n[i] = s1[i];
	i--;
	while ((size_t)++i < len1 + len2)
		n[i] = s2[(size_t)i - len1];
	return (n);
}
