
#include "cub3d.h"



void 	my_pixel_put(t_window *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int engine(t_parser *par)
{
	t_window	win;

	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, par->res.width, par->res.height, "lol");
	win.img = mlx_new_image(win.mlx, par->res.width, par->res.height);
	win.addr = mlx_get_data_addr(win.img, &(win.bpp), &(win.line_length), &(win.endian));
	for(int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
			my_pixel_put(&win, y, x, 0x00FF0000);
	}
	mlx_put_image_to_window(win.mlx, win.win, win.img, 0, 0);
	mlx_loop(win.mlx);
	return (0);
}
