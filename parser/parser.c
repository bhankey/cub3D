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

static void	init_text(t_texture *tex)
{
	tex->img = NULL;
	tex->addr = NULL;
	tex->path = NULL;
}

static void	init_parser(t_parser *parser)
{
	parser->res.width = -1;
	parser->res.height = -1;
	init_text(&(parser->north_texture));
	init_text(&(parser->sprite_texture));
	init_text(&(parser->west_texture));
	init_text(&(parser->east_texture));
	init_text(&(parser->south_texture));
	parser->floor_color.red = -1;
	parser->floor_color.green = -1;
	parser->floor_color.blue = -1;
	parser->ceiling_color.red = -1;
	parser->ceiling_color.green = -1;
	parser->ceiling_color.blue = -1;
	parser->map.map = NULL;
	parser->map.map_cols = -1;
	parser->map.player.i = -1;
	parser->parser_flags = 0;
	parser->map.s_count = 0;
}

static void	parse_all_stuff(t_parser *parser, int fd)
{
	char	*line;
	int		map_started;
	int		gnl_status;

	map_started = 0;
	while (!map_started && (gnl_status = get_next_line(fd, &line)) > 0)
	{
		if (line[0] == '\0')
			free(line);
		else
		{
			if (ft_isalpha(line[0]))
			{
				parse_parameters(parser, line);
				free(line);
			}
			else
				exit_with_einval_error();
			if (parser->parser_flags == 255)
				map_started = 1;
		}
	}
	if (!map_started || gnl_status <= -1)
		exit_with_einval_error();
	parser->map.map = parse_and_check_map(&(parser->map), fd);
}

int			parser(t_parser *parser, char *file_name)
{
	int		fd;

	init_parser(parser);
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	parse_all_stuff(parser, fd);
	parser->ceiling_color.rgb = parser->ceiling_color.red;
	parser->ceiling_color.rgb = (parser->ceiling_color.rgb << 8) +
			parser->ceiling_color.green;
	parser->ceiling_color.rgb = (parser->ceiling_color.rgb << 8) +
								parser->ceiling_color.blue;
	parser->floor_color.rgb = parser->floor_color.red;
	parser->floor_color.rgb = (parser->floor_color.rgb << 8) +
								parser->floor_color.green;
	parser->floor_color.rgb = (parser->floor_color.rgb << 8) +
								parser->floor_color.blue;
	return (0);
}
