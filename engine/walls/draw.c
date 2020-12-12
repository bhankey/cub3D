/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:19:07 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:19:09 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		check_edges(t_all *all, t_point *one, t_point *second)
{
	if (one->y < 0)
		one->y = 0;
	if (one->y > all->parser->res.height)
		one->y = all->parser->res.height - 1;
	if (second->y > all->parser->res.height)
		second->y = all->parser->res.height - 1;
	if (second->y < 0)
		second->y = 0;
}

static void		put_one_pixel_line(t_all *all, t_point one, int color)
{
	pixel_put(all->manager, (int)(roundf(one.x)),
		(int)(roundf(one.y)), color);
}


void draw_strip(t_all *all, t_point one, int y2, int color)
{
	while (one.y != y2)
	{
		pixel_put(all->manager, one.x, one.y, color);
		one.y++;
	}
}
//void			line_dda(t_all *all, t_point one, t_point second, int color)
//{
//	int		length;
//	int		length_back;
//	double	x;
//	double	y;
//
//	check_edges(all, &one, &second);
//	if (abs((int)((roundf(one.x)) - (roundf(second.x)))) <
//	abs((int)((roundf(one.y)) - (roundf(second.y)))))
//		length = abs((int)(roundf(one.y)) - (int)(roundf(second.y)));
//	else
//		length = abs((int)(roundf(one.x)) - (int)(roundf(second.x)));
//	if (length == 0)
//		return (put_one_pixel_line(all, one, color));
//	x = one.x;
//	y = one.y;
//	length_back = length;
//	length++;
//	while (length--)
//	{
//		x += (second.x - one.x) / length_back;
//		y += (second.y - one.y) / length_back;
//		pixel_put(all->manager, roundf(x), roundf(y), color);
//	}
//}
