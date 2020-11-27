

#include "cub3d.h"
int main()
{
	t_parser pas;

	parser(&pas, "map.cub");
	char **l = pas.map.map;
	while (*l)
	{
		printf("%s\n", *l);
		l++;
	}
	engine(&pas);

	exit( 0);
}
