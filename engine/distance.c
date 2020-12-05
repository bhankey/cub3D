
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

float 	normalize_angle(float angle)
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
	int 		is_ray_facing_down;
	int 		is_ray_facing_right;
	float		next_horizontal_touch_x;
	float		next_horizontal_touch_y;
	int			is_wall_hit;

	is_wall_hit = 0;
	ray_angle = normalize_angle(ray_angle);
	is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	is_ray_facing_right = ray_angle < M_PI / 2 || ray_angle > 1.5 * M_PI;
	player = *(all->player);
	player.y_step = SCALE;
	player.x_step = SCALE / tanf(ray_angle);
	player.y_intercept = ((int)((player.y / SCALE))) * SCALE;
	player.y_intercept += is_ray_facing_down ? SCALE : 0;
	player.x_intercept = player.x + (player.y_intercept - player.y) / tanf(ray_angle);
	player.y_step *= (!is_ray_facing_down) ? -1 : 1;
	player.x_step *= (!is_ray_facing_right && player.x_step > 0) ? -1 : 1;
	player.x_step *= (is_ray_facing_right && player.x_step < 0) ? -1 : 1;
	next_horizontal_touch_x = player.x_intercept;
	next_horizontal_touch_y = player.y_intercept;
	while (next_horizontal_touch_x >= 0 && next_horizontal_touch_x <= all->parser->map.map_cols * SCALE &&
		   next_horizontal_touch_y >= 0 && next_horizontal_touch_y <= all->parser->map.map_rows * SCALE)
	{
		if (is_wall_at(all, next_horizontal_touch_x, next_horizontal_touch_y - (!is_ray_facing_down ? 1.0f : 0.0f)))
		{
			is_wall_hit = 1;
			player.x_step = next_horizontal_touch_x;
			player.y_step = next_horizontal_touch_y;
			break;
		}
		else
		{
			next_horizontal_touch_x += player.x_step;
			next_horizontal_touch_y += player.y_step;
		}
	}
	return (is_wall_hit == 1 ? sqrtf((player.x_step - player.x) * (player.x_step - player.x) + (player.y_step - player.y) * (player.y_step - player.y)) : -1.0f);
}

float	vertical_intersection(t_all *all, float ray_angle)
{
	t_player	player;
	int 		is_ray_facing_down;
	int 		is_ray_facing_right;
	float		next_vertical_touch_x;
	float		next_vertical_touch_y;
	int			is_wall_hit;

	is_wall_hit = 0;
	ray_angle = normalize_angle(ray_angle);
	is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	is_ray_facing_right = ray_angle < M_PI / 2 || ray_angle > 1.5 * M_PI;
	player = *(all->player);
	player.x_step = SCALE;
	player.y_step = SCALE * tanf(ray_angle);
	player.x_intercept = ((int)((player.x / SCALE))) * SCALE;
	player.x_intercept += is_ray_facing_right ? SCALE : 0;
	player.y_intercept = player.y + (player.x_intercept - player.x) * tanf(ray_angle);
	player.x_step *= (!is_ray_facing_right) ? -1 : 1;
	player.y_step *= (!is_ray_facing_down && player.y_step > 0) ? -1 : 1;
	player.y_step *= (is_ray_facing_down && player.y_step < 0) ? -1 : 1;
	next_vertical_touch_x = player.x_intercept;
	next_vertical_touch_y = player.y_intercept;
	while (next_vertical_touch_x >= 0 && next_vertical_touch_x <= all->parser->map.map_cols * SCALE &&
		   next_vertical_touch_y >= 0 && next_vertical_touch_y <= all->parser->map.map_rows * SCALE)
	{
		if (is_wall_at(all, next_vertical_touch_x - (!is_ray_facing_right ? 1.0f : 0.0f), next_vertical_touch_y))
		{
			is_wall_hit = 1;
			player.x_step = next_vertical_touch_x;
			player.y_step = next_vertical_touch_y;
			break;
		}
		else
		{
			next_vertical_touch_x += player.x_step;
			next_vertical_touch_y += player.y_step;
		}
	}
	return (is_wall_hit == 1 ? sqrtf((player.x_step - player.x) * (player.x_step - player.x) + (player.y_step - player.y) * (player.y_step - player.y)) : -1.0f);
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
