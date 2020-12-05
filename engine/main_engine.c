
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
	line_dda(all, ray_id, (all->parser->res.height / 2) - (wall_height / 2),
			 ray_id,
			 (all->parser->res.height / 2) - (wall_height / 2) + wall_height,
			 0xFFFFFF);
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
		//render_ray(all, distance, ray_angle);
		render_3d(all, distance, i++, ray_angle);
	}
}

void 	fill_and_print_image(t_all *all, t_parser *par)
{
	all->manager->img = mlx_new_image(all->manager->mlx, par->res.width, par->res.height);
	all->manager->addr = mlx_get_data_addr(all->manager->img, &(all->manager->bpp), &(all->manager->line_length), &(all->manager->endian));
	//print_map(par->map.map, all->manager, 0, 0);
	//draw_player(all);
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

int		engine(t_parser *par)
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
