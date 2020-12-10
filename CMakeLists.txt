cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_C_STANDARD 99)
set(FLAGS "-L -lmlx -lXext -lX11 -lm")
set(LIBX libmlx)
set(LIBX_PATH ../minilibx-linux/libmlx.a)
set(LIBFT libft)
set(LIBFT_PATH ../libft/libft.a)
include_directories(includes libft minilibx-linux gnl)
add_library(${LIBX} STATIC IMPORTED)
add_library(${LIBFT} STATIC IMPORTED)
set_property(TARGET ${LIBX} PROPERTY IMPORTED_LOCATION ${LIBX_PATH})
set_property(TARGET ${LIBFT} PROPERTY IMPORTED_LOCATION ${LIBFT_PATH})
add_executable(cub3D main.c parser/parse_map.c parser/parser.c parser/parser_identifiers.c
        utilits/different_utils.c gnl/get_next_line.c libft/ft_atoi.c libft/ft_isdigit.c
        libft/ft_isspace.c libft/ft_isalpha.c gnl/get_next_line_utils.c
        libft/ft_lstnew.c libft/ft_lstadd_back.c libft/ft_calloc.c libft/ft_lstclear.c
        libft/ft_lstdelone.c libft/ft_strlen.c libft/ft_bzero.c libft/ft_lstsize.c libft/ft_memset.c
        utilits/different_utils.c utilits/list_utilits.c engine/main_engine.c engine/walls/wall_functions.c engine/walls/draw.c engine/utils/pixel_put.c engine/textures/init_textures.c
        engine/walls/render_wall.c engine/sprites/sprite_render.c engine/sprites/sprite_init.c engine/sprites/sprite_helper_to_print.c engine/player/player.c engine/walls/distance_to_wall.c engine/walls/distance_to_wall_second.c
        gnl/get_next_line_utils_s.c engine/utils/exit_functions.c engine/player/move_functions.c screenshot/screenshot.c engine/utils/different_engine_utils.c)
target_link_libraries(${PROJECT_NAME} ${LIBX} ${FLAGS})
target_link_libraries(${PROJECT_NAME} ${LIBFT})