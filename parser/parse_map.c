/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:21:43 by bhankey           #+#    #+#             */
/*   Updated: 2020/11/25 20:21:45 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list		*parse_to_map(t_map *map, int fd)
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
	if (gnl_status <= -1)
		exit_with_einval_error();
	if (*line == '\0')
		free(line);
	else
	{
		buf = ft_lstnew(line);
		if (buf == NULL)
			exit_with_einval_error();
		ft_lstadd_back(&head, buf);
	}
	return (head);
}

static void			reallocate_list(t_list **list, int size, int i)
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
		i = 0;
		line = (old_list)->content;
		new_line = (char *)ft_calloc(size + 2, sizeof(char));
		if (new_line == NULL)
			exit_with_einval_error();
		while (line[i] != '\0')
		{
			new_line[i] = line[i];
			i++;
		}
		new_line[i] = '\0';
		buf = ft_lstnew(new_line);
		if (buf == NULL)
			exit_with_einval_error();
		ft_lstadd_back(&new_head, buf);
		old_list = old_list->next;
	}
	ft_lstclear(list, remove_str);
	*list = new_head;
}

static char			**list_to_arr(t_list **list, t_map *map)
{
	int		size;
	char	**arr_map;
	t_list	*buf;
	int		i;

	size = ft_lstsize(*list);
	arr_map = ft_calloc(size + 1, sizeof(char *));
	if (arr_map == NULL)
		exit_with_einval_error();
	reallocate_list(list, map->map_cols, size);
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

static int			check_for_forbidden_helper(char ch, int i)
{
	if ((ch == 'N' || ch == 'S' || ch == 'W' || ch == 'E') && i == -1)
		return (1);
	return (0);
}

static void			check_for_forbidden_helper_v2(t_map *map, int i, int *j,
											char ch)
{
	map->player.i = i;
	map->player.j = *j;
	map->player.orientation = ch;
	(*j)++;
}

static int			check_for_forbidden_helper_v3(char ch)
{
	if (ch == '0' || ch == '1' || ch == '2' || ch == ' ')
		return (1);
	return (0);
}

static void			check_for_forbidden_char(t_map *map)
{
	char	**arr_map;
	int		i;
	int		j;
	int		is_end;

	i = 0;
	is_end = 0;
	arr_map = map->map;
	while (arr_map[i])
	{
		j = 0;
		if (arr_map[i][0] != '\0' && is_end == 1)
			exit_with_einval_error();
		if (arr_map[i][0] == '\0')
		{
			is_end = 1;
			free(arr_map[i]);
			arr_map[i] = NULL;
		}
		else
			while (arr_map[i][j] != '\0')
				if (check_for_forbidden_helper(arr_map[i][j], map->player.i))
					check_for_forbidden_helper_v2(map, i, &j, arr_map[i][j]);
				else if (check_for_forbidden_helper_v3(arr_map[i][j]))
					j++;
				else
					exit_with_einval_error();
		i++;
	}
}

static void			flood_fill(t_map *map, int x, int y)
{
	if ((x >= 0 && y >= 0 && x < map->map_rows && map->map[x][y] != '\0' &&
		 (map->map[x][y] == '0' || map->map[x][y] == '2') &&
	map->map[x][y] != ' ') || (x == map->player.i && y == map->player.j))
	{
		if (map->map[x][y] == '0')
			map->map[x][y] = '-';
		if (map->map[x][y] == '2')
			map->map[x][y] = '+';
		flood_fill(map, x + 1, y);
		flood_fill(map, x - 1, y);
		flood_fill(map, x, y + 1);
		flood_fill(map, x, y - 1);
	}
	else if ((x >= map->map_rows || y < 0 || x < 0) ||
			 (map->map[x][y] != '1' && map->map[x][y] != '-' && map->map[x][y] != '+'))
		exit_with_einval_error();
}

static void			flood_fill_check(t_map *map)
{
	t_point point;

	point.x = map->player.i;
	point.y = map->player.j;
	flood_fill(map, point.x, point.y);
}

char				**parse_and_check_map(t_map *map, int fd)
{
	t_list	*l_map;

	l_map = parse_to_map(map, fd);
	map->map = list_to_arr(&l_map, map);
	check_for_forbidden_char(map);
	if (map->player.i == -1)
		exit_with_einval_error();
	map->map_rows = 0;
	while (map->map[map->map_rows])
		map->map_rows++;
	flood_fill_check(map);
	return (map->map);
}
