

#include "cub3d.h"

int 	end_on_cub(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i < 5)
		exit_with_einval_error();
	if (str[i - 1] != 'b' && str[i - 2] != 'u' && str[i - 3] != 'c' &&
	str[i - 4] != '.')
		exit_with_einval_error();
	return (1);
}

int		main(int argc, char **argv)
{
	t_parser pas;

	if (argc == 1 || argc > 3)
		exit_with_einval_error();
	if (argc == 3)
		if (ft_strncmp(argv[2], "--save", 7))
			exit_with_einval_error();
	end_on_cub(argv[1]);
	parser(&pas, argv[1]);
	if (argc == 2)
		engine(&pas);
	else
		make_screenshot(&pas);
	exit( 0);
}
