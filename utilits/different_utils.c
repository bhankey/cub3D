
#include "cub3d.h"

void exit_with_error_print(void)
{
	perror("Error\n");
	exit(EXIT_FAILURE);
}

void exit_with_einval_error(void)
{
	strerror(EINVAL);
	exit_with_error_print();
}