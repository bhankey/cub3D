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

SRCS	=	main.c parser/parse_map.c parser/parser.c parser/parse_in_list.c utilits/list_utilits.c GNL/get_next_line.c GNL/get_next_line_utils.c

NAME	=	cub3D

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	= -Wall -Wextra -Werror -I ./includes -I ./libft -I ./$(MLX_D) -I ./GNL

ifeq ($(shell uname), Linux)
	MLX_D = minilibx-linux
	MLX = -L minilibx-linux -lmlx -lXext -lX11 -lbsd

else
	MLX_D = minilibx_mms_20200219
	MLX = -L minilibx_mms_20200219 -lmlx -framework OpenGL -framework AppKit

endif

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) bonus -C libft
			$(MAKE) -C 	$(MLX_D)
			$(CC) $(CFALGS) -o $(NAME) $(OBJS) ./libft/libft.a $(MLX) -lm

clean:
			rm -f $(OBJS)
			$(MAKE) clean -C libft
			$(MAKE) clean -C $(MLX_D)

fclean:		clean
			$(MAKE) fclean -C libft
			rm -f $(NAME)
re:			fclean all

.PHONY: 	all clean fclean re