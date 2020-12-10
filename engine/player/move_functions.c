/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 22:54:27 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/10 22:54:29 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_for_walls(t_all *all, int x, int y)
{
	return (all->parser->map.map[x][y] != '1'
	&& all->parser->map.map[x][y] != '0' && all->parser->map.map[x][y] != ' '
	&& all->parser->map.map[x][y] != '2' && all->parser->map.map[x][y] != '+');
}

void		move_forward(t_all *all)
{
	if (check_for_walls(all, (int)((all->player->y -
		(sinf(all->player->dir) * 5)) / SCALE),
		(int)((all->player->x - (cosf(all->player->dir) * 5)) / SCALE)))
	{
		all->player->y -= (sinf(all->player->dir)) * 5;
		all->player->x -= (cosf(all->player->dir)) * 5;
	}
}

void		move_back(t_all *all)
{
	if (check_for_walls(all, (int)((all->player->y +
		(sinf(all->player->dir) * 5)) / SCALE),
		(int)((all->player->x + (cosf(all->player->dir) * 5)) / SCALE)))
	{
		all->player->y += (sinf(all->player->dir)) * 5;
		all->player->x += (cosf(all->player->dir)) * 5;
	}
}

void		move_left(t_all *all)
{
	if (check_for_walls(all, (int)((all->player->y + (sinf(all->player->dir
	- M_PI / 2)) * 5) / SCALE), (int)((all->player->x
		+ (cosf(all->player->dir - M_PI / 2)) * 5) / SCALE)))
	{
		all->player->y += (sinf(all->player->dir - M_PI / 2)) * 5;
		all->player->x += (cosf(all->player->dir - M_PI / 2)) * 5;
	}
}

void		move_right(t_all *all)
{
	if (check_for_walls(all, (int)((all->player->y -
	(sinf(all->player->dir - M_PI / 2)) * 5) / SCALE), (int)((all->player->x
	- (cosf(all->player->dir - M_PI / 2)) * 5) / SCALE)))
	{
		all->player->y -= (sinf(all->player->dir - M_PI / 2)) * 5;
		all->player->x -= (cosf(all->player->dir - M_PI / 2)) * 5;
	}
}
