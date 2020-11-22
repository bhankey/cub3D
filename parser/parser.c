/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:17:31 by bhankey           #+#    #+#             */
/*   Updated: 2020/11/22 17:17:36 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_parser(t_parser *parser)
{
	parser->resolution.width = 1920;
	parser->resolution.height = 1080;
	parser->north_texture = "./textures/north_texture";
	parser->south_texture = "./textures/south_texture";
	parser->west_texture = "./textures/west_texture";
	parser->east_texture = "./textures/east_texture";
	parser->sprite_texture = "./textures/sprite";
	parser->floor_color.red = 128;
	parser->floor_color.green = 128;
	parser->floor_color.blue = 128;
	parser->ceiling_color.red = 0;
	parser->ceiling_color.green = 191;
	parser->ceiling_color.blue = 255;
	parser->map = NULL;
}


int			parser(t_parser *parser, char *file_name)
{
	int		fd;
	t_list	*list;
//	char	*map_first_line;
	t_list *h;

	init_parser(parser);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (-1);

	return (0);
}
