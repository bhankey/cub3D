
#include "cub3d.h"

int engine(t_parser *parser)
{
	t_window win;

	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, parser->resolution.width, parser->resolution.height, "lol");
	mlx_loop(win.mlx);
	return (0);
}
