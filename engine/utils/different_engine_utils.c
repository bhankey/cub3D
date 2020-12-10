/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   different_engine_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 22:54:42 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/10 22:54:45 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_res(t_all *all)
{
	int x;
	int y;

	mlx_get_screen_size(all->manager->mlx, &x, &y);
	if (all->parser->res.width > x)
		all->parser->res.width = x;
	if (all->parser->res.height > y)
		all->parser->res.height = y;
}
