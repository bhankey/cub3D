/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 04:32:20 by bhankey           #+#    #+#             */
/*   Updated: 2020/11/22 04:32:22 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB3D_H
# define CUB3D_CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "fcntl.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>

/*
** define scale for normal results
*/

# define SCALE 16

/*
** All structures
*/

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct		s_resolution
{
	int				width;
	int				height;
}					t_resolution;

typedef struct		s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_color;

typedef struct		s_parser
{
	t_resolution	resolution;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*sprite_texture;
	t_color			floor_color;
	t_color			ceiling_color;
	char			**map;
}					t_parser;

/*
** Parser
*/

char				*parser_identifiers(t_parser *parser, int fd);
int					parser(t_parser *parser, char *file_name);
t_list				*parse_in_list(t_list **list, int fd);
void				remove_str(void *content);
int					parse_list_to_structer(t_parser *parser, t_list **list)

#endif