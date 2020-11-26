

#include "cub3d.h"
int main()
{
	t_parser pas;

	parser(&pas, "map.cub");
	char **l = pas.map.map;
	//engine(&pas);

	while (*l)
	{
		printf("%s\n", *l);
		l++;
	}
	exit( 0);
}
