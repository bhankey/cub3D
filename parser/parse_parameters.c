/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:12:31 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/12 14:12:33 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_north(t_parser *parser, char *line)
{
	if ((parser->parser_flags & 2u) != 0)
		exit_with_einval_error();
	else
		parse_texture(parser, line);
}

static void	parse_south(t_parser *parser, char *line)
{
	if ((parser->parser_flags & 4u) != 0)
		exit_with_einval_error();
	else
		parse_texture(parser, line);
}

void		parse_parameters(t_parser *parser, char *line)
{
	if (*line == 'R' && *(line + 1) == ' ')
		parse_resolution(parser, line);
	else if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
		parse_north(parser, line);
	else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
		parse_south(parser, line);
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
	else if ((*line == 'F' || *line == 'C') && *(line + 1) == ' ')
		parse_color(parser, line);
	else
		exit_with_einval_error();
}
