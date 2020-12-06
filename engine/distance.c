
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
	return (all->parser->map.map[map_y][map_x] == '1' ||
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

float	horizontal_intersection(t_all *all, float ray_angle)
{
	t_player	player;
	int			is_ray_down;
	int			is_ray_facing_right;
	float		n_t_x;
	float		n_t_y;

	all->player->is_wall_hit = 0;
	ray_angle = normalize_angle(ray_angle);
	is_ray_down = ray_angle > 0 && ray_angle < M_PI;
	is_ray_facing_right = ray_angle < M_PI / 2 || ray_angle > 1.5 * M_PI;
	player = *(all->player);
	player.y_step = SCALE;
	player.x_step = SCALE / tanf(ray_angle);
	player.y_inter = ((int)((player.y / SCALE))) * SCALE;
	player.y_inter += is_ray_down ? SCALE : 0;
	player.x_inter = player.x + (player.y_inter - player.y) / tanf(ray_angle);
	player.y_step *= (!is_ray_down) ? -1 : 1;
	player.x_step *= (!is_ray_facing_right && player.x_step > 0) ? -1 : 1;
	player.x_step *= (is_ray_facing_right && player.x_step < 0) ? -1 : 1;
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
		{
			n_t_x += player.x_step;
			n_t_y += player.y_step;
		}
	return (all->player->is_wall_hit == 1 ? sqrtf(powf((n_t_x - player.x),
		2) + powf((n_t_y - player.y), 2)) : -1.0f);
}

float	vertical_intersection(t_all *all, float angle)
{
	t_player	player;
	int			is_ray_facing_down;
	int			is_ray_right;
	float		n_t_x;
	float		n_t_y;

	all->player->is_wall_hit = 0;
	angle = normalize_angle(angle);
	is_ray_facing_down = angle > 0 && angle < M_PI;
	is_ray_right = angle < M_PI / 2 || angle > 1.5 * M_PI;
	player = *(all->player);
	player.x_step = SCALE;
	player.y_step = SCALE * tanf(angle);
	player.x_inter = ((int)((player.x / SCALE))) * SCALE;
	player.x_inter += is_ray_right ? SCALE : 0;
	player.y_inter = player.y + (player.x_inter - player.x) * tanf(angle);
	player.x_step *= (!is_ray_right) ? -1 : 1;
	player.y_step *= (!is_ray_facing_down && player.y_step > 0) ? -1 : 1;
	player.y_step *= (is_ray_facing_down && player.y_step < 0) ? -1 : 1;
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
		{
			n_t_x += player.x_step;
			n_t_y += player.y_step;
		}
	return (all->player->is_wall_hit == 1 ? sqrtf(powf((n_t_x - player.x),
				2) + powf((n_t_y - player.y), 2)) : -1.0f);
}

float	find_distance_of_ray(t_all *all, float ray_angle)
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
