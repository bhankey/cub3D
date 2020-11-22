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

/*
** if line is empty - 2
** if line not map - 1
** if line is map - 0
*/

static int	is_not_map_start(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
		if (ft_isspace(line[i]) == 1)
			i++;
	if (line[i] == '\0')
		return (2);
	while (line[i] != '\0')
	{
		if (line[i] == 'R' || (line[i] == 'N' && line[i + 1] == 'O') ||
		(line[i] == 'S' && line[i + 1] == 'O') && (line[i] == 'W' &&
		line[i + 1] == 'E') || (line[i] == 'E' && line[i + 1] == 'A') ||
		line[i] == 'S' || line[i] == 'F' || line[i] == 'C')
			return (1);
		i++;
	}
	return (0);
}


char		*parser_identifiers(t_parser *parser, int fd)
{
	char	*line;
	int		i;
	int 	flag;

	i = 0;
	while ((flag = is_not_map_start(line)))
	{
		if (flag == 2)
			continue ;
		while(ft_isspace(line[i]))
			i++;
		if (line[i] == 'R')
			parse_resolution(parser, line[i]);
		if ((line[i] == 'N' && line[i + 1] == 'O'))

	}
	return (line)
}