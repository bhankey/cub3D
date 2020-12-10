
#include "cub3d.h"

void exit_with_error_print(void)
{
	perror("Error\n");
	exit(EXIT_FAILURE);
}

void exit_with_einval_error(void)
{
	errno = EINVAL;
	exit_with_error_print();
}

t_point make_point(float x, float y)
{
	t_point point;

	point.x = x;
	point.y = y;
	return (point);
}