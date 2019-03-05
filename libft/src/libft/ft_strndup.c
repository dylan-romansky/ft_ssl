/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 21:15:19 by dromansk          #+#    #+#             */
/*   Updated: 2018/11/26 21:22:07 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, size_t n)
{
	int		i;
	char	*s2;

	i = (ft_strlen(s1) < n) ? (ft_strlen(s1) + 1) : n + 1;
	s2 = (char *)malloc(sizeof(char) * i);
	i = -1;
	if (!s2)
		return (NULL);
	while (s1[++i] && (size_t)i < n)
		s2[i] = s1[i];
	s2[i] = '\0';
	return (s2);
}
