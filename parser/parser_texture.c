/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:12:43 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/12 14:12:45 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
