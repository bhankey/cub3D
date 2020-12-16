/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flood_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:12:36 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/12 14:12:38 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void				flood_fill_check(t_map *map)
{
	t_point point;

	point.x = map->player.i;
	point.y = map->player.j;
	flood_fill(map, point.x, point.y);
}
