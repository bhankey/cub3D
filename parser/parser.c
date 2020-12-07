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
	parser->res.width = -1;
	parser->res.height = -1;
	parser->north_texture.path = NULL;
	parser->south_texture.path = NULL;
	parser->west_texture.path = NULL;
	parser->east_texture.path = NULL;
	parser->sprite_texture.path = NULL;
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
	parser->map.sprites_count = 0;
}

static void	parse_parameters(t_parser *parser, char *line)
{
	if (*line == 'R' && *(line + 1) == ' ')
		parse_resolution(parser, line);
	else if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
		if ((parser->parser_flags & 2u) != 0)
			exit_with_einval_error();
		else
			parse_texture(parser, line);
	else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
		if ((parser->parser_flags & 4u) != 0)
			exit_with_einval_error();
		else
			parse_texture(parser, line);
	else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
		if ((parser->parser_flags & 8u) != 0)
			exit_with_einval_error();
		else
			parse_texture(parser, line);
	else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
		if ((parser->parser_flags & 16u) != 0)
			exit_with_einval_error();
		else
			parse_texture(parser, line);
	else if (*line == 'S' && *(line + 1) == ' ')
		if ((parser->parser_flags & 32u) != 0)
			exit_with_einval_error();
		else
			parse_texture(parser, line);
	else if (*line == 'F' && *(line + 1) == ' ')
		parse_color(parser, line);
	else if (*line == 'C' && *(line + 1) == ' ')
		parse_color(parser, line);
	else
		exit_with_einval_error();
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
