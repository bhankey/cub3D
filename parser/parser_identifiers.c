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

static int		parse_color_num(const char *line)
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

static void		ident_color(t_color **color, unsigned int *type,
						const char *line, t_parser *parser)
{
	if (*line == 'F')
	{
		*color = &(parser->floor_color);
		*type = 64;
	}
	else
	{
		*color = &(parser->ceiling_color);
		*type = 128;
	}
}

void			parse_color(t_parser *parser, char *line)
{
	unsigned int	type;
	t_color			*color;

	ident_color(&color, &type, line, parser);
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
