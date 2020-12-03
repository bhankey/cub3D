
#include "cub3d.h"


void 	pixel_put(t_window *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void 	print_upscale(t_window *win, float x, float y, int color)
{
	float i;
	float j;

	i = 0;
	x *= SCALE;
	y *= SCALE;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			pixel_put(win, (int)(x + j), (int)(y + i), color);
			j++;
		}
		i++;
	}
}

void 	print_line_angle(t_window *all, float x, float y, float angle, int distance)
{
	while (distance > 0)
	{
		pixel_put(all, x, y, 0x00FF00);
		x += cosf(angle);
		y += sinf(angle);
		distance--;
	}
}

void 	draw_line(t_all *all,float x, float y, float x1, float y1)
{
	float tmp;
	float hup;
	float _cos;
	float _sin;

	if (x > x1)
	{
		tmp = x;
		x = x1;
		x1 = tmp;
	}
	if (y > y1)
	{
		tmp = y;
		y = y1;
		y1 = tmp;
	}
	hup = sqrtf((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
	_cos = (x1 - x) / hup;
	_sin = (y1 - y) / hup;
	while (x < x1 && y < y1)
	{
		pixel_put(all->manager, (int)x, (int)y, 0xFF0000);
		x += _cos;
		y += _sin;
	}
}

void	print_map(char **map, t_window *win, int x, int y)
{
	int i;
	int j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i] != '\0')
		{
			if (map[j][i] == '1')
				print_upscale(win, (float)(x + i), (float)(j + y), 0xFFFFFF);
			else if (map[j][i] == '+')
				print_upscale(win, (float)(x + i), (float)(j + y), 0xFF0000);
			i++;
		}
		j++;
	}
}

void	init_player(t_player *player, t_parser *par)
{
	player->x = (float)par->map.player.j * SCALE + SCALE / 2;
	player->y = (float)par->map.player.i * SCALE + SCALE / 2;
	if (par->map.player.orientation == 'S')
		player->dir = M_PI/2;
	else if (par->map.player.orientation == 'N')
		player->dir = M_PI + M_PI_2;
	else if (par->map.player.orientation == 'W')
		player->dir = M_PI;
	else
		player->dir = 0;
	player->fov = M_PI / 2.0f;
	player->y_step = SCALE;
	player->x_step = SCALE;
}

void 	draw_square(t_window *win, int x, int y, int size, int color)
{
	int i;
	int j;

	i = x - size / 2;
	while (i < x + size / 2)
	{
		j = y - size / 2;
		while (j < y + size / 2)
			pixel_put(win, i, j++, color);
		i++;
	}
}

void 	draw_player(t_all *all)
{
	draw_square(all->manager, all->player->x, all->player->y, 32 ,0xFF0000);
	fprintf(stderr, "\ncenter_x = %lf\n", all->player->x);
	fprintf(stderr, "\ncenter_y = %lf\n", all->player->y);
}

float 	normalize_angle(float angle)
{
	if (angle < 0)
		angle += (float)(2.0 * M_PI);
	else if (angle > 2.0f * M_PI)
		angle -= (float)(2 * M_PI);
	return (angle);
}

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
	if (!is_ray_facing_down)
		next_horizontal_touch_y--;
	while (next_horizontal_touch_x >= 0 && next_horizontal_touch_x <= all->parser->map.map_cols * SCALE &&
	next_horizontal_touch_y >= 0 && next_horizontal_touch_y <= all->parser->map.map_rows * SCALE)
	{
		if (is_wall_at(all, next_horizontal_touch_x, next_horizontal_touch_y - (!is_ray_facing_down ? 1.0 : 0.0)))
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
	if (!is_ray_facing_right)
		next_vertical_touch_x--;
	while (next_vertical_touch_x >= 0 && next_vertical_touch_x <= all->parser->map.map_cols * SCALE &&
		   next_vertical_touch_y >= 0 && next_vertical_touch_y <= all->parser->map.map_rows * SCALE)
	{
		if (is_wall_at(all, next_vertical_touch_x - (!is_ray_facing_right ? 1 : 0), next_vertical_touch_y))
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

//float 	throw_ray(t_all *all, float ray_angle)
//{
//	float horizontal_distance;
//	float vertical_distance;
//
//	horizontal_distance = horizontal_intersection(all, ray_angle);
//	vertical_distance = vertical_intersection(all, ray_angle);
//}
//
//void 	render_ray(t_all *all, float distance, float  ray_angle)
//{
//
//}
void 	render_ray(t_all *all, float distance, float ray_angle)
{
	print_line_angle(all->manager, all->player->x, all->player->y, ray_angle, distance);
//	fprintf(stderr,"hor dist = %f", distance);
}

void 	draw_rays(t_all *all)
{
	int num_rays;
	int ray_id;
	float ray_angle;
	float distance;

	ray_id = 0;
	num_rays = all->parser->res.width;
	ray_angle = all->player->dir - (all->player->fov / 2);
	int i;
	i = 0;
	while (i < num_rays)
	{
		distance = find_distance_of_ray(all, ray_angle);
		i++;
		ray_angle += all->player->fov / num_rays;
		render_ray(all, distance, ray_angle);
	}
}

void 	fill_and_print_image(t_all *all, t_parser *par)
{
	all->manager->img = mlx_new_image(all->manager->mlx, par->res.width, par->res.height);
	all->manager->addr = mlx_get_data_addr(all->manager->img, &(all->manager->bpp), &(all->manager->line_length), &(all->manager->endian));
	print_map(par->map.map, all->manager, 0, 0);
	draw_player(all);
	draw_rays(all);
	mlx_put_image_to_window(all->manager->mlx, all->manager->win, all->manager->img, 0, 0);
	mlx_destroy_image(all->manager->mlx, all->manager->img);
}

int		move_player(int keycode, t_all *all)
{
	fprintf(stderr, "%d\n", keycode);
	if (keycode == 65361)
		all->player->dir -= 0.05f;
	else if (keycode == 65363)
		all->player->dir += 0.05f;
	else if (keycode == 65364)
	{
		if (all->parser->map.map[(int)((all->player->y - (sinf(all->player->dir) * 5)) / SCALE)][(int)((all->player->x - (cosf(all->player->dir) * 5)) / SCALE)] != '1')
		{
			all->player->y -= (sinf(all->player->dir)) * 5;
			all->player->x -= (cosf(all->player->dir)) * 5;
		}
	}
	else if (keycode == 65362)
	{
		if (all->parser->map.map[(int)((all->player->y + (sinf(all->player->dir) * 5)) / SCALE)][(int)((all->player->x + (cosf(all->player->dir) * 5)) / SCALE)] != '1')
		{
			all->player->y += (sinf(all->player->dir)) * 5;
			all->player->x += (cosf(all->player->dir)) * 5;
		}
	}
	else if (keycode == 65307)
	{
		mlx_destroy_window(all->manager->mlx, all->manager->win);
		exit(EXIT_SUCCESS);
	}
	if (all->player->dir < 0)
		all->player->dir += (float)(2 * M_PI);
	else if (all->player->dir > 2.0f * M_PI)
		all->player->dir -= (float)(2 * M_PI);
	fill_and_print_image(all, all->parser);
	return (1);
}

int engine(t_parser *par)
{
	t_all	all;
	t_window window;
	t_player player;

	all.player = &player;
	all.manager = &window;
	all.parser = par;
	init_player(all.player, par);
	all.manager->mlx = mlx_init();
	all.manager->win = mlx_new_window(all.manager->mlx, par->res.width, par->res.height, "cub3D");
	fill_and_print_image(&all, par);
	mlx_hook(window.win, 2, (1L << 0), move_player, &all);
	mlx_loop(all.manager->mlx);
	return (0);
}
