/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:18:47 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:18:48 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		malloc_error(void)
{
	exit_with_error_print();
}

void		sprite_text_error(void)
{
	exit_with_einval_error();
}

static void	destroy_images(t_all *all)
{
	if (all->parser->sprite_texture.img != NULL)
		mlx_destroy_image(all->manager->mlx, all->parser->sprite_texture.img);
	if (all->parser->south_texture.img != NULL)
		mlx_destroy_image(all->manager->mlx, all->parser->south_texture.img);
	if (all->parser->west_texture.img != NULL)
		mlx_destroy_image(all->manager->mlx, all->parser->west_texture.img);
	if (all->parser->east_texture.img != NULL)
		mlx_destroy_image(all->manager->mlx, all->parser->east_texture.img);
	if (all->parser->north_texture.img != NULL)
		mlx_destroy_image(all->manager->mlx, all->parser->north_texture.img);
}

void		exit_when_all_good(t_all *all, int error_code)
{
	int i;

	i = 0;
	while (all->parser->map.map[i] != NULL)
		free(all->parser->map.map[i++]);
	free(all->parser->map.map);
	free(all->parser->south_texture.path);
	free(all->parser->north_texture.path);
	free(all->parser->east_texture.path);
	free(all->parser->west_texture.path);
	free(all->parser->sprite_texture.path);
	free(all->sprites);
	destroy_images(all);
	if (all->manager->win != NULL)
		mlx_destroy_window(all->manager->mlx, all->manager->win);
	if (error_code == 2)
		malloc_error();
	if (error_code == 1)
		sprite_text_error();
	exit(0);
}
