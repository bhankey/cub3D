/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 05:03:13 by bhankey           #+#    #+#             */
/*   Updated: 2020/11/05 05:03:14 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcat_gnl(char *dst, const char *src)
{
	char	*dest;
	char	*srcs;

	dest = dst;
	srcs = (char *)src;
	while (*dest)
		dest++;
	while (*srcs != '\0' && *srcs != '\n')
		*dest++ = *srcs++;
	if (*srcs == '\n')
		*dest++ = '\n';
	*dest = '\0';
	return (dest - dst + 1);
}

void	init_string(t_line *string)
{
	string->line = NULL;
	string->capacity = 512;
	string->len = 0;
}

int		helper_for_alloc(t_line *string)
{
	string->len = -1;
	return (-1);
}

int		n_func(char **line, t_buf *buf)
{
	if (buf->eof_n == 1)
	{
		*line = malloc(2);
		if (line == NULL)
			return (-1);
		(*line)[0] = '\n';
		(*line)[1] = '\0';
		buf->eof_n = 0;
	}
	else
	{
		*line = malloc(1);
		if (line == NULL)
			return (-1);
		(*line)[0] = '\0';
		buf->eof_n = 0;
	}
	return (0);
}

int		helper_for_a_func(t_buf *buf, char *str)
{
	buf->eof_n = 2;
	*str = '\0';
	return (1);
}
