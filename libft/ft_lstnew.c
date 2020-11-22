/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:51:57 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:51:59 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list *node;

	node = (t_list *)malloc(sizeof(t_list) * 1);
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->content = content;
	return (node);
}
