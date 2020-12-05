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
# include <math.h>

/*
** define scale for normal results
*/

# define SCALE 64

/*
** All structures
*/

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_length;
	int			bpp;
	int			endian;
}				t_window;

typedef struct		s_resolution
{
	int				width;
	int				height;
}					t_resolution;

typedef struct		s_player_map
{
	int 			i;
	int 			j;
	char			orientation;
}					t_player_map;

typedef struct 		s_player
{
	float 			x;
	float			y;
	float			dir;
	float			x_step;
	float			y_step;
	float			x_intercept;
	float			y_intercept;
	int 			was_hit_vertical;
	float 			fov;
}					t_player;

typedef struct		s_color
{
	int				red;
	int				green;
	int				blue;
	int 			rgb;
}					t_color;

typedef struct		s_map
{
	char			**map;
	t_player_map 	player;
	int 			map_cols;
	int 			map_rows;
}					t_map;

typedef struct		s_texture
{
	char			*texture;
	void 			*img;
}					t_texture;
/*
** parser_flag
** 00000000 - nothing parsed
** 00000001 - resolution_parsed
** 00000010 - north_texture_parsed
** 00000100 - south_texture_parsed
** 00001000 - west_texture_parsed
** 00010000 - east_texture_parsed
** 00100000 - sprite_parsed
** 01000000 - floor_color_parsed
** 10000000 - ceiling_color_parsed
 */

typedef struct		s_parser
{
	unsigned char 	parser_flags;
	t_resolution	res;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*sprite_texture;
	t_color			floor_color;
	t_color			ceiling_color;
	t_map 			map;
}					t_parser;

typedef struct		s_all
{
	t_window		*manager;
	t_player		*player;
	t_parser		*parser;
}					t_all;
/*
** Parser
*/

char				*parser_identifiers(t_parser *parser, int fd);
int					parser(t_parser *parser, char *file_name);
t_list				*parse_in_list(t_list **list, int fd);
void				remove_str(void *content);
void				parse_resolution(t_parser *parser,char *line);
void				parse_texture(t_parser *parser,char *line);
void				parse_color(t_parser *parser,char *line);
char				**parse_and_check_map(t_map *map,int fd);
void				exit_with_error_print(void);
void				exit_with_einval_error(void);

/*
** Engine
*/

int					engine(t_parser *par);
void 				pixel_put(t_window *data, int x, int y, int color);

/*
** Draw functions
*/


void				line_dda(t_all *all, float x1, float y1, float x2,
					float y2, int color);
void				pixel_put(t_window *data, int x, int y, int color);

/*
** Find distance functions
*/

float				find_distance_of_ray(t_all *all, float ray_angle);
int					is_wall_at(t_all *all, float x, float y);a

/*
** extra functions
*/

void 				print_upscale(t_window *win, float x, float y, int color);
void				print_map(char **map, t_window *win, int x, int y);

#endif
