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
** define size of one block
*/

# define SCALE 64

/*
** All structures
*/

typedef struct		s_point
{
	float 			x;
	float 			y;
}					t_point;

typedef struct 		s_sprites
{
	float			x;
	float 			y;
	float 			distance;
	float 			sprite_dir;
	float 			size;
}					t_sprites;

typedef struct		s_window
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	int				line_length;
	int				bpp;
	int				endian;
}					t_window;

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
	float			x_inter;
	float			y_inter;
	float 			x_wall_meet;
	float 			y_wall_meet;
	float 			fov;
	int 			was_hit_vertical;
	int 			is_wall_hit;
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
	int 			s_count;
}					t_map;

typedef struct		s_texture
{
	char			*path;
	void 			*img;
	char			*addr;
	int				line_length;
	int				bpp;
	int				endian;
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
	t_texture 		north_texture;
	t_texture 		south_texture;
	t_texture 		west_texture;
	t_texture 		east_texture;
	t_texture		sprite_texture;
	t_color			floor_color;
	t_color			ceiling_color;
	t_map 			map;
}					t_parser;

typedef struct		s_all
{
	t_window		*manager;
	t_player		*player;
	t_parser		*parser;
	t_sprites		*sprites;
	float 			*rays_distance;
}					t_all;

t_point				make_point(float x, float y);

/*
** Parser
*/

int					parser(t_parser *parser, char *file_name);
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

void				render_3d(t_all *all, float distance, int ray_id, float ray_angle);
void				line_dda(t_all *all, t_point one, t_point second,
					int color);
void				pixel_put(t_window *data, int x, int y, int color);
void				update_screen(t_all *all, t_parser *par);

/*
** Find distance functions
*/

float				find_distance_of_ray(t_all *all, float ray_angle);
int					is_wall_at(t_all *all, float x, float y);
float				normalize_angle(float angle);
void				intersection_help(t_player *player, float  *n_t_x,
						  float *n_t_y);

/*
** init functions
*/

void				init_textures(t_all *all);

/*
** exit functions
*/

void 				exit_when_all_good(t_all *all, int error_code);

/*
** Sprite functions
*/

void				find_distance_b_sprite_and_player(t_all *all);
int					is_sprite_in_fov(t_sprites *sprite);
void				find_angle_b_sprite_and_player(t_all *all);
void				sort_spites(t_all *all, int start, int end);
void				init_sprites(t_all *all);
void				render_sprites(t_all *all);

/*
** Player functions
*/

void				init_player(t_player *player, t_parser *par);
int					move_player(int keycode, t_all *all);

#endif
