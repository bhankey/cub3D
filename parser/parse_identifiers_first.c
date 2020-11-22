
#include "cub3d.h"

static void parse_resolution(t_parser *parser, char **line)
{
	char *str;

	str = *line;
}

static void parse_identifiers(t_parser *parser, char **line, int *flag)
{
	char *str;

	str = *line;
	if (*str == 'R' && *(str + 1) == ' ')
		parse_resolution(parser, line);
	else if (*str == 'N' && *(str + 1) == 'O' && *(str + 2) == ' ')
	{
	}
	else if (*str == 'S' && *(str + 1) == 'O' && *(str + 2) == ' ')
	{}
	else if (*str == 'W' && *(str + 1) == 'E' && *(str + 2) == ' ')
	{}
	else if (*str == 'E' && *(str + 1) == 'A' && *(str + 2) == ' ')
	{}
	else if (*str == 'S' && *(str + 1) == ' ')
	{}
	else if (*str == 'F' && *(str + 1) == ' ')
	{}
	else if (*str == 'C' && *(str + 1) == ' ')
	{}
	else
		*flag = 1;
};

int	parse_list_to_structer(t_parser *parser, t_list **list)
{
	char	*line;
	t_list	*buf;
	int 	map_started;
	char 	**map;

	map_started = 0;
	while ((*list))
	{
		line = (*list)->content;
		(*list)->content = NULL;
		buf = (*list);
		(*list) = (*list)->next;
		ft_lstdelone(buf, remove_str);
		if (map_started == 0)
			parse_identifiers();
		else
			parse_map
	}
}