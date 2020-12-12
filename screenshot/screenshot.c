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
	unsigned char	bitmap[52];
	unsigned int	buf;

	ft_bzero(bitmap, 52);
	buf = all->parser->res.width * all->manager->bpp / 8 *
			all->parser->res.height + 54;
	bitmap[0] = (unsigned char)(buf);
	bitmap[1] = (unsigned char)(buf >> 8);
	bitmap[2] = (unsigned char)(buf >> 16);
	bitmap[3] = (unsigned char)(buf >> 24);
	bitmap[8] = (unsigned char)54;
	bitmap[12] = (unsigned char)40;
	bitmap[16] = (unsigned char)((int)all->parser->res.width);
	bitmap[17] = (unsigned char)((int)all->parser->res.width >> 8);
	bitmap[18] = (unsigned char)((int)all->parser->res.width >> 16);
	bitmap[19] = (unsigned char)((int)all->parser->res.width >> 24);
	bitmap[20] = (unsigned char)((int)all->parser->res.height);
	bitmap[21] = (unsigned char)((int)all->parser->res.height >> 8);
	bitmap[22] = (unsigned char)((int)all->parser->res.height >> 16);
	bitmap[23] = (unsigned char)((int)all->parser->res.height >> 24);
	bitmap[24] = (unsigned char)1;
	bitmap[26] = (unsigned char)(all->manager->bpp);
	if (write(fd, bitmap, 52) != 52)
		exit_with_einval_error();
}

void	write_data(t_all *all, int fd)
{
	int len_str;
	int i;

	len_str = all->manager->bpp / 8 * all->parser->res.width;
	i = 0;
	while (i < all->parser->res.height)
	{
		write(fd, all->manager->addr + i * all->manager->line_length, len_str);
		i++;
	}
}

void	bmp_maker(t_all *all)
{
	int				fd;

	fd = open("sreenshot.bmp", O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
		exit_when_all_good(all, 1);
	write(fd, "BM", 2);
	init_bitmap(all, fd);
	write_data(all, fd);
	close(fd);
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
