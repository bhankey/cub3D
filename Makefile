# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 01:59:37 by bhankey           #+#    #+#              #
#    Updated: 2020/10/31 01:59:39 by bhankey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c parser/parse_map.c parser/parser.c parser/parser_identifiers.c utilits/list_utilits.c \
 			utilits/different_utils.c gnl/get_next_line.c gnl/get_next_line_utils.c engine/main_engine.c \
 			engine/walls/draw.c engine/walls/distance_to_wall.c engine/utils/pixel_put.c engine/textures/init_textures.c \
 			engine/utils/exit_functions.c engine/walls/wall_functions.c engine/walls/render_wall.c \
 			engine/sprites/sprite_render.c engine/sprites/sprite_init.c engine/sprites/sprite_helper_to_print.c \
 			engine/player/player.c engine/walls/distance_to_wall_second.c gnl/get_next_line_utils_s.c \
 			engine/player/move_functions.c screenshot/screenshot.c engine/utils/different_engine_utils.c \


NAME	=	cub3D

OBJS	=	$(SRCS:.c=.o)

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -O3 -I ./includes -I ./libft -I ./$(MLX_D) -I ./gnl

ifeq ($(shell uname), Linux)
	MLX_D = minilibx-linux
	MLX = -L minilibx-linux -lmlx -lXext -lX11 -lbsd
	MLX_MAC =  
else
	MLX_D = minilibx_mms_20200219
	MLX = -L $(MLX_D) -lmlx -framework OpenGL -framework AppKit
	MLX_MAC = cp $(MLX_D)/libmlx.dylib ./

endif

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) bonus -C libft
			$(MAKE) -C 	$(MLX_D)
			$(MLX_MAC)
			$(CC) $(CFALGS) -o $(NAME) $(OBJS) -O3 ./libft/libft.a $(MLX) -lm

clean:
			rm -f $(OBJS)
			$(MAKE) clean -C libft
			$(MAKE) clean -C $(MLX_D)

fclean:		clean
			$(MAKE) fclean -C libft
			rm -f $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re
