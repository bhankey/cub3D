/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   different_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 22:55:55 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/10 22:55:57 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		exit_with_error_print(void)
{
	perror("Error\n");
	exit(EXIT_FAILURE);
}

void		exit_with_einval_error(void)
{
	errno = EINVAL;
	exit_with_error_print();
}

t_point		make_point(float x, float y)
{
	t_point point;

	point.x = x;
	point.y = y;
	return (point);
}
