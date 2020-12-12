/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:19:07 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:19:09 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_strip(t_all *all, t_point one, int y2, int color)
{
	while (one.y != y2)
	{
		pixel_put(all->manager, one.x, one.y, color);
		one.y++;
	}
}
