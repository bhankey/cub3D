/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_reallocate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:17:03 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/12 14:17:05 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			reallocate_list_helper(char *line, char *new_line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		new_line[i] = line[i];
		(i)++;
	}
	new_line[i] = '\0';
}

static void			reallocate_list(t_list **list, int size)
{
	t_list	*buf;
	t_list	*old_list;
	t_list	*new_head;
	char	*line;
	char	*new_line;

	old_list = *list;
	new_head = NULL;
	while (old_list)
	{
		line = (old_list)->content;
		new_line = (char *)ft_calloc(size + 2, sizeof(char));
		if (new_line == NULL)
			exit_with_einval_error();
		reallocate_list_helper(line, new_line);
		buf = ft_lstnew(new_line);
		if (buf == NULL)
			exit_with_einval_error();
		ft_lstadd_back(&new_head, buf);
		old_list = old_list->next;
	}
	ft_lstclear(list, remove_str);
	*list = new_head;
}

char				**list_to_arr(t_list **list, t_map *map)
{
	int		size;
	char	**arr_map;
	t_list	*buf;
	int		i;

	size = ft_lstsize(*list);
	arr_map = ft_calloc(size + 1, sizeof(char *));
	if (arr_map == NULL)
		exit_with_einval_error();
	reallocate_list(list, map->map_cols);
	buf = *list;
	i = 0;
	while (buf)
	{
		arr_map[i++] = buf->content;
		buf->content = NULL;
		buf = buf->next;
	}
	arr_map[i] = NULL;
	ft_lstclear(list, remove_str);
	return (arr_map);
}
