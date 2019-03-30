/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 21:15:19 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/29 16:47:54 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*s2;

	i = ft_strlen(s1);
	i = i > n ? n : i;
	if (!(s2 = ft_strnew(i)))
		return (NULL);
	s2 = (char *)ft_memcpy(s2, s1, i);
	return (s2);
}
