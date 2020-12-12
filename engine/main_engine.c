/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:19:22 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:19:24 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_all(t_all *all)
{
	int		num_rays;
	float	ray_angle;
	float	distance;
	int		i;

	num_rays = all->parser->res.width;
	if ((all->rays_distance = ft_calloc(num_rays, sizeof(float))) == NULL)
		exit_when_all_good(all, 2);
	ray_angle = all->player->dir - (all->player->fov / 2);
	i = 0;
	while (i < num_rays)
	{
		distance = find_distance_of_ray(all, ray_angle);
		all->rays_distance[i] = distance;
		ray_angle += all->player->fov / (float)num_rays;
		render_3d(all, distance, i++, ray_angle);
	}
	render_sprites(all);
	free(all->rays_distance);
	all->rays_distance = NULL;
}

void	update_screen(t_all *all, t_parser *par)
{
	if ((all->manager->img = mlx_new_image(all->manager->mlx,
						par->res.width, par->res.height)) == NULL)
		exit_when_all_good(all, 2);
	if ((all->manager->addr = mlx_get_data_addr(all->manager->img,
	&(all->manager->bpp), &(all->manager->line_length),
	&(all->manager->endian))) == NULL)
		exit_when_all_good(all, 2);
	render_all(all);
	mlx_put_image_to_window(all->manager->mlx, all->manager->win,
					all->manager->img, 0, 0);
	mlx_destroy_image(all->manager->mlx, all->manager->img);
}

int		exit_with_cross(void *all_)
{
	t_all *all;

	all = all_;
	exit_when_all_good(all, 0);
	return (0);
}

int		engine(t_parser *par)
{
	t_all		all;
	t_window	window;
	t_player	player;

	all.player = &player;
	all.manager = &window;
	all.parser = par;
	all.manager->win = NULL;
	if ((all.manager->mlx = mlx_init()) == NULL)
		exit_when_all_good(&all, 2);
	check_res(&all);
	all.sprites = NULL;
	init_textures(&all);
	init_sprites(&all);
	init_player(all.player, par);
	if ((all.manager->win = mlx_new_window(all.manager->mlx, par->res.width,
								par->res.height, "cub3D")) == NULL)
		exit_when_all_good(&all, 2);
	update_screen(&all, par);
	mlx_hook(window.win, 17, (1L << 17), exit_with_cross, &all);
	mlx_hook(window.win, 2, (1L << 0), move_player, &all);
	mlx_loop(all.manager->mlx);
	return (0);
}
