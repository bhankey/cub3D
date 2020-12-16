/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:17:56 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:17:59 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		print_if_normal(t_all *all, t_point screen, t_point texture)
{
	int color;

	if (screen.y > 0 && screen.y < all->parser->res.height)
	{
		color = *((int *)(all->parser->sprite_texture.addr +
				((int)texture.y * all->parser->sprite_texture.line_length +
				(int)texture.x * (all->parser->sprite_texture.bpp / 8))));
		if (color != 9961608)
			pixel_put(all->manager, screen.x, screen.y, color);
	}
}

void			print_sprite_texture(t_all *all, float sprite_height,
							t_point start, t_sprites *sprite)
{
	float	y_screen;
	float	x_screen;
	float	x_texture;
	float	y_texture;

	x_screen = start.x;
	x_texture = 0;
	while (x_screen < start.x + sprite_height)
	{
		if (x_screen > 0 && x_screen < all->parser->res.width &&
			sprite->distance < all->rays_distance[(int)x_screen])
		{
			y_screen = start.y;
			y_texture = 0;
			while (y_screen < start.y + sprite_height)
			{
				print_if_normal(all, make_point(x_screen, y_screen),
				make_point(x_texture, y_texture));
				y_screen++;
				y_texture += (SCALE / sprite_height);
			}
		}
		x_screen++;
		x_texture += (SCALE / sprite_height);
	}
}

void			draw_sprite(t_all *all, t_sprites *sprite)
{
	float x_place;
	float y_place;
	float sprite_height;
	float pix_p_degree;
	float dst_prj;

	dst_prj = ((all->parser->res.width / 2.0) / tanf(all->player->fov / 2.0));
	pix_p_degree = all->parser->res.width / all->player->fov;
	sprite_height = dst_prj * (SCALE / sprite->distance);
	x_place = pix_p_degree * sprite->sprite_dir - sprite_height / 2;
	y_place = all->parser->res.height / 2.0 - sprite_height / 2.0;
	if (is_sprite_in_fov(sprite))
		print_sprite_texture(all, sprite_height, make_point(x_place, y_place),
					sprite);
}

void			render_sprites(t_all *all)
{
	int i;

	i = all->parser->map.s_count - 1;
	find_angle_b_sprite_and_player(all);
	find_distance_b_sprite_and_player(all);
	sort_spites(all, 0, all->parser->map.s_count - 1);
	while (i >= 0)
		draw_sprite(all, &(all->sprites[i--]));
}
