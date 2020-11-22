/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:53:04 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:54:04 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void	*))
{
	t_list *node;

	if (lst == NULL || del == NULL)
		return ;
	while ((*lst)->next != NULL)
	{
		node = *lst;
		(*lst) = (*lst)->next;
		(*del)(node->content);
		free(node);
	}
	node = *lst;
	(*del)(node->content);
	(*lst) = NULL;
	free(node);
}
