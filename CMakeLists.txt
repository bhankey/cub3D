cmake_minimum_required(VERSION 3.17)
project(cub3D C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-l../libft/libft.a)
include_directories(includes libft minilibx-linux)
add_executable(cub3D main.c parser/parse_map.c parser/parser.c)
#target_link_libraries(cub3D ./home/sergey/Documents/school_21/cub3D/libft/libft.a)
#target_link_libraries(cub3D libft/libft.a)