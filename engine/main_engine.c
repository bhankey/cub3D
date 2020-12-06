
#include "cub3d.h"



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
	player->fov = M_PI / 3.0f;
	player->y_step = SCALE;
	player->x_step = SCALE;
}


void 	print_texture_horizontal(t_all *all, t_texture *texture, float y_start,
						float wall_height, int x)
{
	float		y_text;
	float		y_end;
	int			color;
	int			j;
	int			touch_dot;

	touch_dot = (int)all->player->x_wall_meet & 0x3F;
	y_text = (y_start - all->parser->res.height / 2 + wall_height / 2) *
			(SCALE / wall_height);
	y_end = y_start + wall_height;
	if (y_end > all->parser->res.height)
		y_end = all->parser->res.height - 1;
	if (y_end < 0)
		y_end = 0;
	j = y_start;
	while (j < y_end)
	{
		color = *((int *)(texture->addr + ((int)y_text * texture->line_length +
				touch_dot * (texture->bpp / 8))));
		pixel_put(all->manager, x, j++, color);
		y_text += (SCALE / wall_height);
	}
}

void 	print_texture_vertical(t_all *all, t_texture *texture, float y_start,
								 float wall_height, int x)
{
	float		y_text;
	float		y_end;
	int			color;
	int			j;
	int			touch_dot;

	touch_dot = (int)all->player->y_wall_meet & 0x3F;
	y_text = (y_start - all->parser->res.height / 2 + wall_height / 2) *
			(SCALE / wall_height);
	y_end = y_start + wall_height;
	if (y_end > all->parser->res.height)
		y_end = all->parser->res.height - 1;
	if (y_end < 0)
		y_end = 0;
	j = y_start;
	while (j < y_end)
	{
		color = *((int *)(texture->addr + ((int)y_text * texture->line_length +
										   touch_dot * (texture->bpp / 8))));
		pixel_put(all->manager, x, j++, color);
		y_text += (SCALE / wall_height);
	}
}

void 	print_wall(t_all *all, int x, float y_start, float wall_height, float angle)
{
	int is_facing_right;
	int is_facing_down;

	angle = normalize_angle(angle);
	float y_end = y_start + wall_height;
	if (y_start < 0)
		y_start = 0;
	if (y_start  > all->parser->res.height)
		y_start = all->parser->res.height - 1;
	if (y_end > all->parser->res.height)
		y_end = all->parser->res.height - 1;
	if (y_end < 0)
		y_end = 0;
	is_facing_right = angle < M_PI / 2 || angle > 1.5 * M_PI;
	is_facing_down = angle > 0 && angle < M_PI;
	if (all->player->was_hit_vertical == 1)
	{
		if (is_facing_right)
		{
			print_texture_vertical(all, &(all->parser->east_texture), y_start, wall_height, x);
		}
		else
		{
			print_texture_vertical(all, &(all->parser->west_texture), y_start, wall_height, x);
		}
	}
	else
	{

		if (is_facing_down)
		{
			print_texture_horizontal(all, &(all->parser->south_texture), y_start, wall_height, x);
		}
		else
		{
			print_texture_horizontal(all, &(all->parser->north_texture), y_start, wall_height, x);
		}
	}
}

void	render_3d(t_all *all, float distance, int ray_id, float ray_angle)
{
	float wall_height;
	float dist_project;
	float correct_dist;

	correct_dist = distance * cosf(ray_angle - all->player->dir);
	dist_project = (all->parser->res.width / 2.0) / tanf(all->player->fov / 2.0);
	wall_height = (SCALE / correct_dist) * dist_project;
	line_dda(all, ray_id, 0, ray_id,
			 (all->parser->res.height / 2) - (wall_height / 2),
			 all->parser->ceiling_color.rgb);
	print_wall(all, ray_id, (all->parser->res.height / 2) - (wall_height / 2), wall_height, ray_angle);
	line_dda(all, ray_id,
			 (all->parser->res.height / 2) - (wall_height / 2) + wall_height,
			 ray_id, all->parser->res.height, all->parser->floor_color.rgb);
}

void 	draw_rays(t_all *all)
{
	int num_rays;
	float ray_angle;
	float distance;

	num_rays = all->parser->res.width;
	ray_angle = all->player->dir - (all->player->fov / 2);
	int i;
	i = 0;
	while (i < num_rays)
	{
		distance = find_distance_of_ray(all, ray_angle);
		ray_angle += all->player->fov / num_rays;
		render_3d(all, distance, i++, ray_angle);
	}
}

void 	fill_and_print_image(t_all *all, t_parser *par)
{
	all->manager->img = mlx_new_image(all->manager->mlx, par->res.width, par->res.height);
	all->manager->addr = mlx_get_data_addr(all->manager->img, &(all->manager->bpp), &(all->manager->line_length), &(all->manager->endian));
	draw_rays(all);
	mlx_put_image_to_window(all->manager->mlx, all->manager->win, all->manager->img, 0, 0);
	mlx_destroy_image(all->manager->mlx, all->manager->img);
}

int		move_player(int keycode, t_all *all)
{
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

void	init_textures(t_all *all)
{
	t_parser	*par;
	int			x;
	int			y;

	par = all->parser;
	par->west_texture.img = mlx_xpm_file_to_image(all->manager->mlx, par->west_texture.path, &x, &y);
	par->west_texture.addr = mlx_get_data_addr(par->west_texture.img, &(par->west_texture.bpp), &(par->west_texture.line_length), &(par->west_texture.endian));
	if (par->west_texture.img == NULL || par->west_texture.addr == NULL)
		exit_with_error_print();
	par->east_texture.img = mlx_xpm_file_to_image(all->manager->mlx, par->east_texture.path, &x, &y);
	par->east_texture.addr = mlx_get_data_addr(par->east_texture.img, &(par->east_texture.bpp), &(par->east_texture.line_length), &(par->east_texture.endian));
	if (par->east_texture.img == NULL || par->east_texture.addr == NULL)
		exit_with_error_print();
	par->south_texture.img = mlx_xpm_file_to_image(all->manager->mlx, par->south_texture.path, &x, &y);
	par->south_texture.addr = mlx_get_data_addr(par->south_texture.img, &(par->south_texture.bpp), &(par->south_texture.line_length), &(par->south_texture.endian));
	if (par->south_texture.img == NULL || par->south_texture.addr == NULL)
		exit_with_error_print();
	par->north_texture.img = mlx_xpm_file_to_image(all->manager->mlx, par->north_texture.path, &x, &y);
	par->north_texture.addr = mlx_get_data_addr(par->north_texture.img, &(par->north_texture.bpp), &(par->north_texture.line_length), &(par->north_texture.endian));
	if (par->north_texture.img == NULL || par->north_texture.addr == NULL)
		exit_with_error_print();
	par->sprite_texture.img = mlx_xpm_file_to_image(all->manager->mlx, par->sprite_texture.path, &x, &y);
	par->sprite_texture.addr = mlx_get_data_addr(par->sprite_texture.img, &(par->sprite_texture.bpp), &(par->sprite_texture.line_length), &(par->sprite_texture.endian));
	if (par->sprite_texture.img == NULL || par->sprite_texture.addr == NULL)
		exit_with_error_print();
}

int		engine(t_parser *par)
{
	t_all	all;
	t_window window;
	t_player player;

	all.player = &player;
	all.manager = &window;
	all.parser = par;
	all.manager->mlx = mlx_init();
	init_textures(&all);
	init_player(all.player, par);
	all.manager->win = mlx_new_window(all.manager->mlx, par->res.width, par->res.height, "cub3D");
	fill_and_print_image(&all, par);
	mlx_hook(window.win, 2, (1L << 0), move_player, &all);
	mlx_loop(all.manager->mlx);
	return (0);
}
