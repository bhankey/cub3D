/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_to_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:19:03 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:19:05 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		horizontal_help(t_player *player, float ray_angle)
{
	int			is_ray_down;
	int			is_ray_facing_right;

	is_ray_down = ray_angle > 0 && ray_angle < M_PI;
	is_ray_facing_right = ray_angle < M_PI / 2 || ray_angle > 1.5 * M_PI;
	player->y_step = SCALE;
	player->x_step = SCALE / tanf(ray_angle);
	player->y_inter = ((int)((player->y / SCALE))) * SCALE;
	player->y_inter += is_ray_down ? SCALE : 0;
	player->x_inter = player->x + (player->y_inter - player->y) /
		tanf(ray_angle);
	player->y_step *= (!is_ray_down) ? -1 : 1;
	player->x_step *= (!is_ray_facing_right && player->x_step > 0) ? -1 : 1;
	player->x_step *= (is_ray_facing_right && player->x_step < 0) ? -1 : 1;
}

static float	horizontal_intersection(t_all *all, float ray_angle)
{
	t_player	player;
	int			is_ray_down;
	float		n_t_x;
	float		n_t_y;

	all->player->is_wall_hit = 0;
	ray_angle = normalize_angle(ray_angle);
	player = *(all->player);
	is_ray_down = ray_angle > 0 && ray_angle < M_PI;
	horizontal_help(&player, ray_angle);
	n_t_x = player.x_inter;
	n_t_y = player.y_inter;
	while (n_t_x >= 0 && n_t_x <= all->parser->map.map_cols * SCALE &&
		n_t_y >= 0 && n_t_y <= all->parser->map.map_rows * SCALE)
		if (is_wall_at(all, n_t_x, n_t_y - (!is_ray_down ? 1.0f : 0.0f)))
		{
			all->player->x_wall_meet = n_t_x;
			all->player->is_wall_hit = 1;
			break ;
		}
		else
			intersection_help(&player, &n_t_x, &n_t_y);
	return (all->player->is_wall_hit == 1 ? sqrtf(powf((n_t_x - player.x),
			2) + powf((n_t_y - player.y), 2)) : -1.0f);
}

static void		vertical_help(t_player *player, float angle)
{
	int			is_ray_facing_down;
	int			is_ray_right;

	is_ray_facing_down = angle > 0 && angle < M_PI;
	is_ray_right = angle < M_PI / 2 || angle > 1.5 * M_PI;
	player->x_step = SCALE;
	player->y_step = SCALE * tanf(angle);
	player->x_inter = ((int)((player->x / SCALE))) * SCALE;
	player->x_inter += is_ray_right ? SCALE : 0;
	player->y_inter = player->y + (player->x_inter - player->x) * tanf(angle);
	player->x_step *= (!is_ray_right) ? -1 : 1;
	player->y_step *= (!is_ray_facing_down && player->y_step > 0) ? -1 : 1;
	player->y_step *= (is_ray_facing_down && player->y_step < 0) ? -1 : 1;
}

static float	vertical_intersection(t_all *all, float angle)
{
	t_player	player;
	int			is_ray_right;
	float		n_t_x;
	float		n_t_y;

	all->player->is_wall_hit = 0;
	angle = normalize_angle(angle);
	is_ray_right = angle < M_PI / 2 || angle > 1.5 * M_PI;
	player = *(all->player);
	vertical_help(&player, angle);
	n_t_x = player.x_inter;
	n_t_y = player.y_inter;
	while (n_t_x >= 0 && n_t_x <= all->parser->map.map_cols * SCALE &&
		n_t_y >= 0 && n_t_y <= all->parser->map.map_rows * SCALE)
		if (is_wall_at(all, n_t_x - (!is_ray_right ? 1.0f : 0.0f), n_t_y))
		{
			all->player->is_wall_hit = 1;
			all->player->y_wall_meet = n_t_y;
			break ;
		}
		else
			intersection_help(&player, &n_t_x, &n_t_y);
	return (all->player->is_wall_hit == 1 ? sqrtf(powf((n_t_x - player.x),
			2) + powf((n_t_y - player.y), 2)) : -1.0f);
}

float			find_distance_of_ray(t_all *all, float ray_angle)
{
	float hor_dist;
	float ver_dist;

	hor_dist = horizontal_intersection(all, ray_angle);
	ver_dist = vertical_intersection(all, ray_angle);
	if (hor_dist == -1)
	{
		all->player->was_hit_vertical = 1;
		return (ver_dist);
	}
	else if (ver_dist == -1)
	{
		all->player->was_hit_vertical = 0;
		return (hor_dist);
	}
	else
	{
		all->player->was_hit_vertical = (ver_dist < hor_dist);
		return (hor_dist < ver_dist ? hor_dist : ver_dist);
	}
}
