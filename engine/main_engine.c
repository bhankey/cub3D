
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
			pixel_put(win, x + j, y + i, color);
			j++;
		}
		i++;
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
	hup = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
	_cos = (x1 - x) / hup;
	_sin = (y1 - y) / hup;
	while (x < x1 && y < y1)
	{
		pixel_put(all->manager, x, y, 0xFF0000);
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
				print_upscale(win, x + i, j + y, 0xFFFFFF);
			else if (map[j][i] == '+')
				print_upscale(win, x + i, j + y, 0xFF0000);
			i++;
		}
		j++;
	}
}

void	init_player(t_player *player, t_parser *par)
{
	player->x = par->map.player.j * SCALE + SCALE / 2;
	player->y = par->map.player.i * SCALE + SCALE / 2;
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
	double pix;

	draw_square(all->manager, all->player->x, all->player->y, 32 ,0xFF0000);
	t_player plr = *(all->player);
	pix = 0;
	while (all->parser->map.map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
	{
		pixel_put(all->manager, plr.x, plr.y, 0xFFFF00);
		plr.x += cos(plr.dir);
		plr.y += sin(plr.dir);
		pix += SCALE;
	}
	pix /= SCALE;
	fprintf(stderr, "\npix = %lf\n", pix);
	fprintf(stderr, "\ncenter_x = %lf\n", all->player->x);
	fprintf(stderr, "\ncenter_y = %lf\n", all->player->y);
}

//void 	draw_rays(t_all *all)
//{
//	int mx = 0;
//	int my = 0;
//	int mp = 0;
//	t_player plr = *(all->player);
//	int dof = 0;
//	float yo, xo;
//	char *map = (char *) all->parser->map.map;
//
//	for (int r = 0; r < 1; r++)
//	{
//		float aTan = -1/tan(plr.dir);
//		if (plr.dir > M_PI)
//		{
//			plr.y =  (((int)all->player->y / 64) * 64) - 0.0001;
//			plr.x = (all->player->y - plr.y) * aTan + all->player->x;
//			yo =-64;
//			xo = -yo * aTan;
//		}
//		if (plr.dir < M_PI)
//		{
//			plr.y =  (((int)all->player->y / 64) * 64) + 64;
//			plr.x = (all->player->y - plr.y) * aTan + all->player->x;
//			yo = 64;
//			xo = -yo * aTan;
//		}
//		if (plr.dir == 0 || plr.dir == M_PI)
//		{
//			plr.x = all->player->x;
//			plr.y = all->player->y;
//			dof = SCALE;
//		}
//		while (dof < all->parser->map.map_rows)
//		{
//			mx = (int)(plr.x) / 64;
//			my = (int)(plr.y) / 64;
//			mp = my * all->parser->map.map_cols + mx;
//			if (mp < all->parser->map.map_cols * all->parser->map.map_rows && map[mp] == 1)
//				dof = all->parser->map.map_rows;
//			else
//			{
//				plr.x += xo;
//				plr.y += yo;
//				dof += 1;
//			}
//
//		}
//		fprintf(stderr, "ray start = x:%f y:%f", all->player->x, all->player->y);
//		fprintf(stderr, "ray end = x:%f y:%f", plr.x, plr.y);
//
//	}
//}

float 	normalize_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2.0f * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int		is_wall_at(t_all *all, float x, float y)
{
	int map_x;
	int map_y;

	if (x < 0 || x > all->parser->map.map_cols * SCALE || y < 0 ||
	y > all->parser->map.map_rows * SCALE)
		return (1);
	map_x = x / SCALE;
	map_y = y / SCALE;
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
	player.x_step = SCALE / tanf(ray_angle);
	player.y_intercept = ((int)((player.y / SCALE))) * SCALE;
	player.y_intercept += is_ray_facing_down ? SCALE : 0;
	player.x_intercept = player.x + (player.y_intercept - player.y) / tan(ray_angle);
	player.y_step *= (!is_ray_facing_down) ? -1 : 1;
	player.x_step = SCALE / tanf(ray_angle);
	player.x_step *= (!is_ray_facing_right && player.x_step > 0) ? -1 : 1;
	player.x_step *= (is_ray_facing_right && player.x_step < 0) ? -1 : 1;
	next_horizontal_touch_x = player.x_intercept;
	next_horizontal_touch_y = player.y_intercept;
	if (!is_ray_facing_down)
		next_horizontal_touch_y--;
	while (next_horizontal_touch_x >= 0 || next_horizontal_touch_x <= all->parser->map.map_cols * SCALE ||
	next_horizontal_touch_y >= 0 || next_horizontal_touch_y <= all->parser->map.map_rows * SCALE)
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
	draw_line(all, player.x, player.y, player.x_step, player.y_step);
	return (is_wall_hit == 1 ? sqrt((player.x_step - player.x) * (player.x_step - player.x) + (player.y_step - player.y) * (player.y_step - player.y)) : -1.0f);
};

float	vertical_intersection(t_all *all, float ray_angle)
{
	t_player player;

	player = *(all->player);
	player.y_step = SCALE * tan(ray_angle);
	return (0);
};


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


void 	draw_rays(t_all *all)
{
//	int num_rays;
//	int ray_id;
//	float ray_angle;
//	float distance;
//
//	ray_id = 0;
//	num_rays = all->parser->res.width;
//	ray_angle = all->player->dir - (all->player->fov / 2);
//	int i;
//	i = 0;
//	while (i < num_rays)
//	{
//		distance = throw_ray(all, ray_angle);
//		i++;
//		ray_angle += all->player->fov / num_rays;
//		render_ray(all, distance, ray_angle);
//	}
	fprintf(stderr,"hor dist = %f", horizontal_intersection(all, all->player->dir));

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
		if (all->parser->map.map[(int)((all->player->y - (sin(all->player->dir) * 5)) / SCALE)][(int)((all->player->x - (cos(all->player->dir) * 5)) / SCALE)] != '1')
		{
			all->player->y -= (sin(all->player->dir)) * 5;
			all->player->x -= (cos(all->player->dir)) * 5;
		}
	}
	else if (keycode == 65362)
	{
		if (all->parser->map.map[(int)((all->player->y + (sin(all->player->dir) * 5)) / SCALE)][(int)((all->player->x + (cos(all->player->dir) * 5)) / SCALE)] != '1')
		{
			all->player->y += (sin(all->player->dir)) * 5;
			all->player->x += (cos(all->player->dir)) * 5;
		}
	}
	else if (keycode == 65307)
	{
		mlx_destroy_window(all->manager->mlx, all->manager->win);
		exit(EXIT_SUCCESS);
	}
	if (all->player->dir < 0)
		all->player->dir += 2 * M_PI;
	else if (all->player->dir > 2.0f * M_PI)
		all->player->dir -= 2 * M_PI;
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
