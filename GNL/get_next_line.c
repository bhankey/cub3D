/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 05:03:16 by bhankey           #+#    #+#             */
/*   Updated: 2020/11/05 05:03:17 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Если память не выделилась - "-1"
**Все нормально				 - "0"
*/

int		string_realloc(t_line *string)
{
	char *tmp;
	char *line;

	if (string->line == NULL)
	{
		string->line = (char *)malloc(string->capacity);
		if (string->line == NULL)
			return (helper_for_alloc(string));
		string->line[0] = '\0';
		return (0);
	}
	tmp = string->line;
	string->line = (char *)malloc(string->capacity * 2);
	string->capacity *= 2;
	if (string->line == NULL)
	{
		string->len = -1;
		free(tmp);
		return (-1);
	}
	line = string->line;
	while (*tmp)
		*line++ = *tmp++;
	*line = '\0';
	return (0);
}

/*
** Прочитали из потока все в баффер(в потоке больше нет символов) - "2"
**В потоке еще есть символы, а баффер мы заполнили				  - "1"
**Из потока нечего брать(Значит в string должна быть строка(EOF)) - "0"
**Ошибка и fd не существует 								      - "-1"
*/

int		gnl_r(int fd, t_buf *buffer)
{
	int bites;

	if ((bites = read(fd, buffer->buf, BUFFER_SIZE)) < 0)
		return (-1);
	if (bites == 0)
		return (0);
	buffer->buf[bites] = '\0';
	if (bites < BUFFER_SIZE)
		return (2);
	return (1);
}

/*
** был в бафере /n и в string полноценная строка - "0"
** в бафере не было /n и нужно еще раз прочитать из потока в бафер - "1"
** Ошибка маллока - "-1"
*/

int		string_buf(t_buf *buffer, t_line *string)
{
	char	*str;
	char	*buf;

	while (string->line == NULL || string->len + BUFFER_SIZE + 2 >
	string->capacity)
		if ((string_realloc(string)) == -1)
			return (-1);
	string->len = ft_strlcat_gnl(string->line, buffer->buf);
	str = buffer->buf;
	buf = buffer->buf;
	while (*str && *str != '\n')
		str++;
	if (*str == '\0')
	{
		*buf = '\0';
		return (1);
	}
	str++;
	while (*str)
		*buf++ = *str++;
	*buf = '\0';
	return (0);
}

int		helper_for_last_line(int flag, t_line *string, char **line, t_buf *buf)
{
	char *str;

	*line = string->line;
	str = string->line;
	if (flag == 0)
	{
		if (*str == '\n' && *(str + 1) == '\0')
			return (helper_for_a_func(buf, str));
		while (*str != '\n' && *str != '\0')
			str++;
		if (*str == '\0')
			return (0);
		buf->eof_n = 2;
		*str = '\0';
		return (1);
	}
	else
	{
		while (*str != '\n' && *str != '\0')
			str++;
		*str = '\0';
		return (flag);
	}
}

int		get_next_line(int fd, char **line)
{
	static t_buf	buf;
	t_line			str;
	int				fd_f;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (buf.eof_n != 0)
		return (n_func(line, &buf));
	init_string(&str);
	if (buf.buf[0] != '\0' && (string_buf(&buf, &str)) == 0 && str.len != -1)
	{
		if (buf.buf[0] == '\0' && gnl_r(fd, &buf) == 0)
			return (helper_for_last_line(0, &str, line, &buf));
		return (helper_for_last_line(1, &str, line, &buf));
	}
	if (((fd_f = gnl_r(fd, &buf)) == -1) || str.len == -1)
		return (-1);
	while (string_buf(&buf, &str) != 0 && str.len != -1)
		if (((fd_f = gnl_r(fd, &buf)) == 2 || fd_f == 0) && buf.buf[0] == '\0')
			return (helper_for_last_line(0, &str, line, &buf));
	if (str.len == -1)
		return (-1);
	if (buf.buf[0] == '\0' && gnl_r(fd, &buf) == 0)
		return (helper_for_last_line(0, &str, line, &buf));
	return (helper_for_last_line(1, &str, line, &buf));
}
