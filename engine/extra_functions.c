
#include "cub3d.h"

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
}