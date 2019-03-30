/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 17:42:07 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/28 18:46:07 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*n;
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((n = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
	{
		n = ft_strcpy(n, s1);
		n = ft_strcat(n, s2);
		return (n);
	}
	return (NULL);
}
