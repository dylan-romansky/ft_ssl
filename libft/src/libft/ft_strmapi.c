/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 17:15:28 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/29 16:38:03 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		a;
	char	*n;

	if (s == NULL || *s == '\0' || f == NULL)
		return (NULL);
	a = -1;
	if (!(n = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[++a] != '\0')
		n[a] = f(a, s[a]);
	n[a] = '\0';
	return (n);
}
