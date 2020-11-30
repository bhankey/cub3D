
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
	player->x = par->map.player.j;
	player->y = par->map.player.i;
	if (par->map.player.orientation == 'S')
		player->dir = M_PI/2;
	else if (par->map.player.orientation == 'N')
		player->dir = M_PI + M_PI_2;
	else if (par->map.player.orientation == 'W')
		player->dir = M_PI;
	else
		player->dir = 0;
	player->fov = M_PI / 4.0f;
}

void 	draw_player(t_all *all)
{
	double pix;

	print_upscale(all->manager, all->player->x, all->player->y, 0x204050);
	t_player plr = *(all->player);
	plr.x = (plr.x * SCALE) + SCALE / 2;
	plr.y = plr.y * SCALE + SCALE / 2;
	pix = 0;
	while (all->parser->map.map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
	{
		pixel_put(all->manager, plr.x, plr.y, 0xFFFF00);
		plr.x += cos(plr.dir);
		plr.y += sin(plr.dir);
		pix += 1.0;
	}
	pix /= SCALE;
	fprintf(stderr, "\npix = %lf\n", pix);
	fprintf(stderr, "\ncenter_x = %lf\n", all->player->x);
	fprintf(stderr, "\ncenter_y = %lf\n", all->player->y);
}

void 	fill_and_print_image(t_all *all, t_parser *par)
{
	all->manager->img = mlx_new_image(all->manager->mlx, par->res.width, par->res.height);
	all->manager->addr = mlx_get_data_addr(all->manager->img, &(all->manager->bpp), &(all->manager->line_length), &(all->manager->endian));
	print_map(par->map.map, all->manager, 0, 0);
	draw_player(all);
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
		all->player->y -= (sin(all->player->dir)) / SCALE * 5 ;
		all->player->x -= (cos(all->player->dir)) / SCALE * 5;
	}
	else if (keycode == 65362)
	{
		all->player->y += (sin(all->player->dir)) / SCALE * 5;
		all->player->x += (cos(all->player->dir)) / SCALE * 5;
	}
	else if (keycode == 65307)
	{
		mlx_destroy_window(all->manager->mlx, all->manager->win);
		exit(EXIT_SUCCESS);
	}
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
