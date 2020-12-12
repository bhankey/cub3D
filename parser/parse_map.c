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

static int			check_for_forbidden_helper(char ch, t_map *map)
{
	if (ch == '2')
		map->s_count++;
	if ((ch == 'N' || ch == 'S' || ch == 'W' || ch == 'E')
	&& map->player.i == -1)
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

	i = 0;
	arr_map = map->map;
	while (arr_map[i])
	{
		j = 0;
		if (arr_map[i][0] == '\0')
		{
			free(arr_map[i]);
			arr_map[i] = NULL;
		}
		else
			while (arr_map[i][j] != '\0')
				if (check_for_forbidden_helper(arr_map[i][j], map))
					check_for_forbidden_helper_v2(map, i, &j, arr_map[i][j]);
				else if (check_for_forbidden_helper_v3(arr_map[i][j]))
					j++;
				else
					exit_with_einval_error();
		i++;
	}
}

char				**parse_and_check_map(t_map *map, int fd)
{
	t_list	*l_map;

	l_map = parse_to_map(map, fd);
	if (l_map == NULL)
		exit_with_einval_error();
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
