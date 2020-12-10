/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:18:15 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:18:42 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_one_texture(t_all *all, t_window *win, t_texture *texture)
{
	int x;
	int y;

	texture->img = mlx_xpm_file_to_image(win->mlx, texture->path, &x, &y);
	if (texture->img == NULL)
		exit_when_all_good(all, 1);
	texture->addr = mlx_get_data_addr(texture->img, &(texture->bpp),
							&(texture->line_length), &(texture->endian));
	if (texture->addr == NULL)
		exit_when_all_good(all, 2);
}

void	init_textures(t_all *all)
{
	t_parser	*par;

	par = all->parser;
	init_one_texture(all, all->manager, &(par->west_texture));
	init_one_texture(all, all->manager, &(par->east_texture));
	init_one_texture(all, all->manager, &(par->south_texture));
	init_one_texture(all, all->manager, &(par->north_texture));
	init_one_texture(all, all->manager, &(par->sprite_texture));
}
