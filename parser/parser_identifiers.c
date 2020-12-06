/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifiers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:17:26 by bhankey           #+#    #+#             */
/*   Updated: 2020/11/22 17:17:27 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			parse_resolution(t_parser *parser, char *line)
{
	if ((parser->parser_flags & 1u) != 0)
		exit_with_einval_error();
	line += 2;
	while (ft_isspace(*line))
		line++;
	parser->res.width = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (ft_isspace(*line))
		line++;
	parser->res.height = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line != '\0' || parser->res.width <= 0 ||
		parser->res.height <= 0)
		exit_with_einval_error();
	parser->parser_flags |= 1;
}

static void		parse_texture_help(t_parser *parser, char *line, char **texture)
{
	if (*line == 'N')
	{
		parser->parser_flags |= 2u;
		parser->north_texture.path = *texture;
	}
	else if (*line == 'S' && *(line + 1) == 'O')
	{
		parser->parser_flags |= 4u;
		parser->south_texture.path = *texture;
	}
	else if (*line == 'W')
	{
		parser->parser_flags |= 8u;
		parser->west_texture.path = *texture;
	}
	else if (*line == 'E')
	{
		parser->parser_flags |= 16u;
		parser->east_texture.path = *texture;
	}
	else
	{
		parser->parser_flags |= 32u;
		parser->sprite_texture.path = *texture;
	}
}

void			parse_texture(t_parser *parser, char *line)
{
	int		i;
	int		j;
	char	*texture;
	int		len;

	i = 3;
	while (ft_isspace(line[i]))
		i++;
	len = 0;
	j = i;
	while (line[j++] != '\0')
		len++;
	texture = (char *)malloc(len + 3);
	j = 0;
	while (line[i] != '\0')
	{
		texture[j++] = line[i++];
	}
	texture[j] = '\0';
	if (*texture == '\0')
		exit_with_einval_error();
	parse_texture_help(parser, line, &texture);
}

static int		parse_color_num(char *line)
{
	int	len;
	int	i;
	int pr;
	int res;

	len = 0;
	i = 0;
	res = 0;
	pr = 1;
	while (line[len] != '\0' && line[len] != ',')
	{
		len++;
		pr *= 10;
	}
	while (len-- && len <= 3)
	{
		pr /= 10;
		res += pr * (line[i++] - '0');
	}
	if (len > 3 || res < 0 || res > 255 || (res == 0 && line[0] != '0'))
		exit_with_einval_error();
	return (res);
}

void			parse_color(t_parser *parser, char *line)
{
	unsigned int	type;
	t_color			*color;

	if (*line == 'F')
	{
		color = &(parser->floor_color);
		type = 64;
	}
	else
	{
		color = &(parser->ceiling_color);
		type = 128;
	}
	if ((parser->parser_flags & type) != 0)
		exit_with_einval_error();
	line += 2;
	while (ft_isspace(*line))
		line++;
	color->red = parse_color_num(line);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	color->green = parse_color_num(line);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	color->blue = parse_color_num(line);
	while (ft_isdigit(*line))
		line++;
	if (*line != '\0')
		exit_with_einval_error();
	parser->parser_flags |= type;
}
