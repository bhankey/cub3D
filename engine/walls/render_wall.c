/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:19:13 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:19:14 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		t_hor(t_all *all, t_texture *texture, t_point start,
				float wall_height)
{
	float		y_text;
	float		y_end;
	int			color;
	int			j;
	int			touch_dot;

	touch_dot = (int)all->player->x_wall_meet & 0x3F;
	if ((int)wall_height % 2 == 1)
		wall_height++;
	y_text = (start.y - all->parser->res.height / 2 + wall_height / 2) *
			(SCALE / wall_height);
	y_end = start.y + wall_height;
	if (y_end > all->parser->res.height)
		y_end = all->parser->res.height - 1;
	if (y_end < 0)
		y_end = 0;
	j = start.y;
	while (j < y_end)
	{
		color = *((int *)(texture->addr + ((int)y_text * texture->line_length +
									touch_dot * (texture->bpp / 8))));
		pixel_put(all->manager, start.x, j++, color);
		y_text += (SCALE / wall_height);
	}
}

static void		t_vert(t_all *all, t_texture *texture, t_point start,
				float wall_height)
{
	float		y_text;
	float		y_end;
	int			color;
	int			j;
	int			touch_dot;

	touch_dot = (int)all->player->y_wall_meet & 0x3F;
	if ((int)wall_height % 2 == 1)
		wall_height++;
	y_text = (start.y - all->parser->res.height / 2 + wall_height / 2) *
			(SCALE / wall_height);
	y_end = start.y + wall_height;
	if (y_end > all->parser->res.height)
		y_end = all->parser->res.height - 1;
	if (y_end < 0)
		y_end = 0;
	j = (int)floorf(start.y);
	while (j < y_end)
	{
		color = *((int *)(texture->addr + ((int)y_text * texture->line_length +
									touch_dot * (texture->bpp / 8))));
		pixel_put(all->manager, start.x, j++, color);
		y_text += (SCALE / wall_height);
	}
}

static void		normalise_y(t_all *all, t_point *start)
{
	if (start->y < 0)
		start->y = 0;
	if (start->y > all->parser->res.height)
		start->y = all->parser->res.height - 1;
}

static void		print_wall(t_all *all, t_point start, float wall_height,
						float angle)
{
	int is_facing_right;
	int is_facing_down;

	angle = normalize_angle(angle);
	normalise_y(all, &start);
	is_facing_right = angle < M_PI / 2 || angle > 1.5 * M_PI;
	is_facing_down = angle > 0 && angle < M_PI;
	if (all->player->was_hit_vertical == 1)
	{
		if (is_facing_right)
			t_vert(all, &(all->parser->east_texture),
				make_point(start.x, start.y), wall_height);
		else
			t_vert(all, &(all->parser->west_texture),
					make_point(start.x, start.y), wall_height);
	}
	else
	{
		if (is_facing_down)
			t_hor(all, &(all->parser->south_texture),
				make_point(start.x, start.y), wall_height);
		else
			t_hor(all, &(all->parser->north_texture),
				make_point(start.x, start.y), wall_height);
	}
}

void			render_3d(t_all *all, float distance, int ray_id,
			float ray_angle)
{
	float wall_height;
	float dist_project;
	float correct_dist;

	correct_dist = distance * cosf(ray_angle - all->player->dir);
	dist_project = (all->parser->res.width / 2.0) /
			tanf(all->player->fov / 2.0);
	wall_height = (SCALE / correct_dist) * dist_project;
	line_dda(all, make_point((float)ray_id, 0.0f), make_point((float)ray_id,
		(all->parser->res.height / 2.0) - (wall_height / 2)),
		all->parser->ceiling_color.rgb);
	print_wall(all, make_point(ray_id,
	(all->parser->res.height / 2.0) - (wall_height / 2)),
			wall_height, ray_angle);
	line_dda(all, make_point((float)ray_id, (all->parser->res.height
	/ 2.0) + (wall_height / 2.0)), make_point((float)ray_id,
			all->parser->res.height), all->parser->floor_color.rgb);
}
