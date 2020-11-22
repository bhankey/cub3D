/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:54:47 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:54:48 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		ft_remove_if_fails(t_list *head, void (*del)(void *))
{
	t_list *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		ft_lstdelone(tmp, del);
	}
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_lst;
	t_list *new_head;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_head = ft_lstnew((*f)(lst->content));
	if (new_head == NULL)
		return (NULL);
	new_lst = new_head;
	lst = lst->next;
	while (lst != NULL)
	{
		new_lst->next = ft_lstnew((*f)(lst->content));
		new_lst = new_lst->next;
		if (new_lst == NULL)
		{
			ft_remove_if_fails(new_head, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new_head);
}
