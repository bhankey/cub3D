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
	parser->resolution.width = -1;
	parser->resolution.height = -1;
	parser->north_texture = "";
	parser->south_texture = "";
	parser->west_texture = "";
	parser->east_texture = "";
	parser->sprite_texture = "";
	parser->floor_color.red = -1;
	parser->floor_color.green = -1;
	parser->floor_color.blue = -1;
	parser->ceiling_color.red = -1;
	parser->ceiling_color.green = -1;
	parser->ceiling_color.blue = -1;
	parser->map.map = NULL;
	parser->map.max_string = 512;
	parser->parser_flags = 0;
}

static void parse_parameters(t_parser *parser, char *line)
{
	if (*line == 'R' && *(line + 1) == ' ')
		parse_resolution(parser, line);
	else if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
		parse_texture(parser, line);
	else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
		parse_texture(parser, line);
	else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
		parse_texture(parser, line);
	else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
		parse_texture(parser, line);
	else if (*line == 'S' && *(line + 1) == ' ')
		parse_texture(parser, line);
	else if (*line == 'F' && *(line + 1) == ' ')
		parse_color(parser, line);
	else if (*line == 'C' && *(line + 1) == ' ')
		parse_color(parser, line);
	else
		exit_with_einval_error();
}

static void parse_all_stuff(t_parser *parser, int fd)
{
	char	*line;
	int		map_started;
	int 	gnl_status;

	gnl_status = 0;
	map_started = 0;
	while (!map_started &&(gnl_status = get_next_line(fd, &line)) > 0)
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
	t_list	*list;

	init_parser(parser);
	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	parse_all_stuff(parser, fd);
	//Распарсить параметры (Если нет какого-то из параметров, то выдаем ошибку
	//Распарсить саму карту (Сначала можем записать в список, потом посчитать самую большую строку,
	// и добиваем размер карты до самой большой строки ' ', далее переписываем все в массив.


	return (0);
}
