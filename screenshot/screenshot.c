/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 22:58:48 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/10 22:58:50 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_bitmap(t_all *all, int fd)
{
	unsigned int	bites_4;
	unsigned short 	bites_2;
	bites_4 = (all->parser->res.width * all->parser->res.height *
					(all->manager->bpp / 8)) + 56;
	write(fd, &bites_4, 4);
	bites_4 = 0;
	write(fd, &bites_4, 4);
	bites_4 = 54;
	write(fd, &bites_4, 4);
	bites_4 = 40;
	write(fd, &bites_4, 4);
	bites_4 = all->parser->res.width;
	write(fd, &bites_4, 4);
	bites_4 = all->parser->res.height;
	write(fd, &bites_4, 4);
	bites_2 = 1;
	write(fd, &bites_2, 2);
	bites_2 = all->manager->bpp;
	write(fd, &bites_2, 2);
	bites_4 = 0;
	write(fd, &bites_4, 4);
	bites_4 = all->parser->res.height * all->parser->res.width;
	write(fd, &bites_4, 4);
	bites_4 = 0;
	write(fd, &bites_4, 4);
	bites_4 = 0;
	write(fd, &bites_4, 4);
	bites_4 = 0;
	write(fd, &bites_4, 4);
	bites_4 = 0;
	write(fd, &bites_4, 4);
}

void	bmp_maker(t_all *all)
{
	int				fd;

	unsigned char	*addres;
	int				i;

	fd = open("sreenshot.bmp", O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		exit_when_all_good(all, 1);
	write(fd, "BM", 2);
	init_bitmap(all, fd);
	i = 0;
	while (i < all->parser->res.height)
	{
		addres = (unsigned char *)all->manager->addr;
		write(fd, &(addres[(all->parser->res.height - (i - 1)) *
			all->manager->line_length]), all->manager->line_length);
		i++;
	}
}

void	make_screenshot(t_parser *par)
{
	t_all		all;
	t_window	window;
	t_player	player;

	all.player = &player;
	all.manager = &window;
	all.parser = par;
	all.manager->win = NULL;
	all.manager->mlx = mlx_init();
	if (all.manager->mlx == NULL)
		exit_when_all_good(&all, 2);
	all.sprites = NULL;
	init_textures(&all);
	init_sprites(&all);
	init_player(all.player, par);
	all.manager->img = mlx_new_image(all.manager->mlx,
									par->res.width, par->res.height);
	all.manager->addr = mlx_get_data_addr(all.manager->img,
	&(all.manager->bpp), &(all.manager->line_length), &(all.manager->endian));
	render_all(&all);
	bmp_maker(&all);
	mlx_destroy_image(all.manager->mlx, all.manager->img);
	exit_when_all_good(&all, 0);
}
