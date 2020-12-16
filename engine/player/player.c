/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:17:25 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:17:28 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player, t_parser *par)
{
	player->x = (float)par->map.player.j * SCALE + SCALE / 2;
	player->y = (float)par->map.player.i * SCALE + SCALE / 2;
	if (par->map.player.orientation == 'S')
		player->dir = M_PI / 2;
	else if (par->map.player.orientation == 'N')
		player->dir = M_PI + M_PI_2;
	else if (par->map.player.orientation == 'W')
		player->dir = M_PI;
	else
		player->dir = 0;
	player->fov = M_PI / 3.0f;
	player->y_step = SCALE;
	player->x_step = SCALE;
}

int		move_player(int keycode, t_all *all)
{
	if (keycode == 65361)
		all->player->dir -= 0.05f;
	else if (keycode == 65363)
		all->player->dir += 0.05f;
	else if (keycode == 119)
		move_back(all);
	else if (keycode == 115)
		move_forward(all);
	else if (keycode == 97)
		move_left(all);
	else if (keycode == 100)
		move_right(all);
	else if (keycode == 65307)
		exit_when_all_good(all, 0);
	if (all->player->dir < 0)
		all->player->dir += (float)(2 * M_PI);
	else if (all->player->dir > 2.0f * M_PI)
		all->player->dir -= (float)(2 * M_PI);
	update_screen(all, all->parser);
	return (1);
}
