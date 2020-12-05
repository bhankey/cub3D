
#include "cub3d.h"

void 	draw_strip(t_all *all, float x, float y, float len)
{
	int i;

	if (y < 0)
	{
		y = 0;
		len = all->parser->res.height - 1;
	}
	i = 0;
	while (i < y)
		pixel_put(all->manager, floorf(x), floorf(i++), all->parser->ceiling_color.rgb);
	while (len > 0)
	{
		pixel_put(all->manager, floorf(x), floorf(y++), 0xFFFFFF);
		len--;
	}
	while (y < all->parser->res.height - 1)
		pixel_put(all->manager, floorf(x), floorf(y++), all->parser->floor_color.rgb);
}

void 	draw_line(t_all *all, int x1, int y1, int x2, int y2)
{
	if (y1 < 0)
	{
		y1 = 0;
	}
	if (y2 > all->parser->res.height)
		y2 = all->parser->res.height - 1;
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int signx = x1 < x2 ? 1 : -1;
	int singy = y1 < y2 ? 1 : -1;
	int error = dx - dy;

	pixel_put(all->manager, x2, y2, 0xFFFFFF);
	while (x1 != x2 || y1 != y2)
	{
		pixel_put(all->manager, x1, y1, 0xFFFFFF);
		int error2 = error * 2;
		if (error2 > -dy)
		{
			error -= dy;
			x1 += signx;
		}
		if (error2 < dx)
		{
			error += dx;
			y1 += singy;
		}
	}
}

void	line_dda(t_all *all, float x1, float y1, float x2, float y2, int color)
{
	if (y1 < 0)
		y1 = 0;
	if (y1 > all->parser->res.height)
		y1 = all->parser->res.height - 1;
	if (y2 > all->parser->res.height)
		y2 = all->parser->res.height - 1;
	if (y2 < 0)
		y2 = 0;
	int iX1 = roundf(x1);
	int iY1 = roundf(y1);
	int iX2 = roundf(x2);
	int iY2 = roundf(y2);
	int deltaX = abs(iX1 - iX2);
	int deltaY = abs(iY1 - iY2);
	int length;
	if (deltaX < deltaY)
		length = deltaY;
	else
		length = deltaX;
	if (length == 0)
	{
		pixel_put(all->manager, iX1, iY1, color);
		return ;
	}
	double dX = (x2 - x1) / length;
	double dY = (y2 - y1) / length;
	double x = x1;
	double y = y1;
	length++;
	while (length--)
	{
		x += dX;
		y += dY;
		pixel_put(all->manager, roundf(x), roundf(y), color);
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
