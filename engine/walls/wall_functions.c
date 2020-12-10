/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:19:16 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:19:19 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall_at(t_all *all, float x, float y)
{
	int map_x;
	int map_y;

	if (x < 0 || x > all->parser->map.map_cols * SCALE || y < 0 ||
		y > all->parser->map.map_rows * SCALE)
		return (1);
	map_x = (int)(x / SCALE);
	map_y = (int)(y / SCALE);
	return (map_x >= all->parser->map.map_cols ||
	map_y >= all->parser->map.map_rows ||
	all->parser->map.map[map_y][map_x] == '1' ||
			all->parser->map.map[map_y][map_x] == ' ' ||
			all->parser->map.map[map_y][map_x] == '\0');
}

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += (float)(2.0 * M_PI);
	else if (angle > 2.0f * M_PI)
		angle -= (float)(2 * M_PI);
	return (angle);
}
