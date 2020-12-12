/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:17:10 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/12 14:17:12 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			parse_to_map_norm_help(t_list **buf, t_list **head,
										char **line, int gnl_status)
{
	if (gnl_status <= -1)
		exit_with_einval_error();
	if (**line == '\0')
		free(*line);
	else
	{
		*buf = ft_lstnew(*line);
		if (*buf == NULL)
			exit_with_einval_error();
		ft_lstadd_back(&(*head), *buf);
	}
}

t_list				*parse_to_map(t_map *map, int fd)
{
	t_list		*head;
	t_list		*buf;
	int			gnl_status;
	char		*line;
	int			map_started;

	map_started = 0;
	head = NULL;
	while ((gnl_status = get_next_line(fd, &line) > 0))
	{
		if (*line == '\0' && map_started == 0)
			free(line);
		else
		{
			map_started = 1;
			if ((long long int)ft_strlen(line) > map->map_cols)
				map->map_cols = ft_strlen(line);
			buf = ft_lstnew(line);
			if (buf == NULL)
				exit_with_einval_error();
			ft_lstadd_back(&head, buf);
		}
	}
	parse_to_map_norm_help(&buf, &head, &line, gnl_status);
	return (head);
}
