/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:04:35 by dromansk          #+#    #+#             */
/*   Updated: 2019/03/29 14:58:52 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *n;
	t_list *head;

	n = f(lst);
	head = n;
	while (lst->next)
	{
		lst = lst->next;
		n->next = f(lst);
		n = n->next;
	}
	return (head);
}
