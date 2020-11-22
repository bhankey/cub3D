/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:17:19 by bhankey           #+#    #+#             */
/*   Updated: 2020/11/22 17:17:22 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		is_empty_line(char *line)
{
	while (*line != '\0')
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

static void		parse_in_list_failure_case(char **line)
{
	free(*line);
	perror("Malloc failure: ");
	exit(EXIT_FAILURE);
}

static void		parse_in_list_failure_case_2(char **line, t_list **list)
{
	ft_lstclear(list, remove_str);
	parse_in_list_failure_case(line);
}

static void		add_line_in_list(t_list **list, t_list **tail, char **line)
{
	t_list *buf;

	if (is_empty_line(*line))
		free(*line);
	else
	{
		if (*list == NULL)
		{
			*list = ft_lstnew(*line);
			if (*list == NULL)
				parse_in_list_failure_case(line);
			*tail = *list;
		}
		else
		{
			buf = ft_lstnew(*line);
			if (buf == NULL)
				parse_in_list_failure_case_2(line, list);
			(*tail)->next = buf;
			*tail = buf;
		}
	}
}

t_list			*parse_in_list(t_list **list, int fd)
{
	char	*line;
	int		gnl_flag;
	t_list	*tail;

	*list = NULL;
	while ((gnl_flag = get_next_line(fd, &line)) > 0)
		add_line_in_list(list, &tail, &line);
	if (gnl_flag == -1)
		parse_in_list_failure_case_2(&line, list);
	tail->next = ft_lstnew(line);
	if (tail->next == NULL)
		parse_in_list_failure_case_2(&line, list);
	return (*list);
}
