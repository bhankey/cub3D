/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_to_wall_second.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:41:27 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 16:41:30 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	intersection_help(t_player *player, float *n_t_x, float *n_t_y)
{
	*n_t_x += player->x_step;
	*n_t_y += player->y_step;
}
