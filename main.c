

#include "cub3d.h"
int main()
{
	t_parser pas;
//	char **l;
	parser(&pas, "map.cub");
//	l = pas.map.map;
	engine(&pas);
//
//	while (*l)
//	{
//		printf("%s\n", *l);
//		l++;
//	}
	exit( 0);
}
