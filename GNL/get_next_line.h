/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:05:56 by bhankey           #+#    #+#             */
/*   Updated: 2020/11/04 01:06:26 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_GET_NEXT_LINE_H
# define GNL_GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

typedef struct	s_line
{
	char		*line;
	int			capacity;
	int			len;
}				t_line;

typedef struct	s_buf
{
	char		buf[BUFFER_SIZE + 1];
	char		eof_n;
}				t_buf;

int				helper_for_alloc(t_line *string);
void			init_string(t_line *string);
int				get_next_line(int fd, char **line);
size_t			ft_strlcat_gnl(char *dst, const char *src);
int				n_func(char **line, t_buf *buf);
int				helper_for_a_func(t_buf *buf, char *str);

#endif
