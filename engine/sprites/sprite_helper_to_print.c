/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helper_to_print.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:17:43 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:17:46 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap_elements(t_sprites *sprites, int left, int right)
{
	t_sprites	tmp;

	tmp = sprites[left];
	sprites[left] = sprites[right];
	sprites[right] = tmp;
}

void	sort_spites(t_all *all, int start, int end)
{
	int			left;
	int			right;
	float		piv;
	t_sprites	*sprites;

	left = start;
	right = end;
	sprites = all->sprites;
	if (start < end)
	{
		piv = sprites[(left + right) / 2].distance;
		while (left <= right)
		{
			while (sprites[left].distance < piv)
				left++;
			while (sprites[right].distance > piv)
				right--;
			if (left <= right)
				swap_elements(sprites, left++, right--);
		}
		sort_spites(all, start, right);
		sort_spites(all, left, end);
	}
}

void	find_angle_b_sprite_and_player(t_all *all)
{
	int i;

	i = 0;
	while (i < all->parser->map.s_count)
	{
		all->sprites[i].sprite_dir =
				atan2f((float)all->sprites[i].y - all->player->y,
					(float)all->sprites[i].x - all->player->x);
		while (all->sprites[i].sprite_dir - all->player->dir > M_PI)
			all->sprites[i].sprite_dir -= 2.0 * M_PI;
		while (all->sprites[i].sprite_dir - all->player->dir < -M_PI)
			all->sprites[i].sprite_dir += 2.0 * M_PI;
		all->sprites[i].sprite_dir -= all->player->dir;
		all->sprites[i].sprite_dir += M_PI / 6.0;
		i++;
	}
}

void	find_distance_b_sprite_and_player(t_all *all)
{
	int i;

	i = 0;
	while (i < all->parser->map.s_count)
	{
		all->sprites[i].distance = sqrtf(powf(all->player->x -
		(float)all->sprites[i].x, 2) + powf(all->player->y -
		(float)all->sprites[i].y, 2));
		i++;
	}
}

int		is_sprite_in_fov(t_sprites *sprite)
{
	if (sprite->sprite_dir <= M_PI / 3.0 ||
	sprite->sprite_dir <= M_PI * 2 - 0.2)
		return (1);
	return (0);
}
