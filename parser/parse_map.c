
#include "cub3d.h"

static t_list		*parse_to_map(t_map *map, int fd)
{
	t_list		*head;
	t_list		*buf;
	int 		gnl_status;
	char 		*line;

	head = NULL;
	while ((gnl_status = get_next_line(fd, &line) > 0))
	{
		if (*line == '\0')
			free(line);
		else
		{
			if (ft_strlen(line) > map->max_string)
				map->max_string = ft_strlen(line);
			buf = ft_lstnew(line);
			if (buf == NULL)
				exit_with_einval_error();
			ft_lstadd_back(&head, buf);
		}
	}
	if (gnl_status <= -1)
		exit_with_einval_error();
	if (*line == '\0')
		free(line);
	else
	{
		buf = ft_lstnew(line);
		if (buf == NULL)
			exit_with_einval_error();
		ft_lstadd_back(&head, buf);
	}
	return (head);
}

static void			reallocate_list(t_list **list, int size, int i)
{
	t_list *buf;
	t_list *old_list;
	t_list *new_head;
	char 	*line;
	char 	*new_line;

	i = 0;
	old_list = *list;
	while (old_list)
	{
		line = (old_list)->content;
		new_line = (char *)ft_calloc(size + 2, sizeof(char));
		if (new_line == NULL)
			exit_with_einval_error();
		while (line[i] != '\0')
		{
			new_line[i] = line[i];
			i++;
		}
		buf = ft_lstnew(new_line);
		if (buf == NULL)
			exit_with_einval_error();
		ft_lstadd_back(&new_head, buf);
		old_list = old_list->next;

	}
	ft_lstclear(list, remove_str);
	*list = new_head;
}

static char			**list_to_arr(t_list **list, t_map *map)
{
	int		size;
	char	**arr_map;
	t_list	*buf;
	int 	i;

	size = ft_lstsize(*list);
	arr_map = ft_calloc(size + 1, sizeof(char *));
	if (arr_map == NULL)
		exit_with_einval_error();
	if (map->max_string > 512)
		reallocate_list(list, map->max_string, size);
	buf = *list;
	i = 0;
	while (buf)
	{
		arr_map[i++] = buf->content;
		buf->content = NULL;
		buf = buf->next;
	}
	arr_map[i] = NULL;
	ft_lstclear(list, remove_str);
	return (arr_map);
}

char				**parse_and_check_map(t_map *map, int fd)
{
	t_list	*l_map;

	l_map = parse_to_map(map, fd);
	map->map = list_to_arr(&l_map, map);
	return (map->map);
}