cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-l../libft/libft.a)
include_directories(includes libft minilibx-linux gnl)
add_executable(cub3D main.c parser/parse_map.c parser/parser.c parser/parser_identifiers.c
        utilits/different_utils.c gnl/get_next_line.c libft/ft_atoi.c libft/ft_isdigit.c
        libft/ft_isspace.c libft/ft_isalpha.c gnl/get_next_line_utils.c
        libft/ft_lstnew.c libft/ft_lstadd_back.c libft/ft_calloc.c libft/ft_lstclear.c
        libft/ft_lstdelone.c libft/ft_strlen.c libft/ft_bzero.c libft/ft_lstsize.c libft/ft_memset.c
        utilits/different_utils.c utilits/list_utilits.c)
#target_link_libraries(cub3D ./home/sergey/Documents/school_21/cub3D/libft/libft.a)
#target_link_libraries(cub3D libft/libft.a)