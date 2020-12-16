/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 13:17:50 by bhankey           #+#    #+#             */
/*   Updated: 2020/12/09 13:17:52 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		shrink_sprites_array_norm_helper(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

static void		shrink_spites_array(t_all *all)
{
	int			count;
	t_sprites	*new;
	int			i;
	int			j;

	i = 0;
	count = 0;
	while (i < all->parser->map.s_count)
	{
		if (all->sprites[i].x != 0)
			count++;
		i++;
	}
	if ((new = ft_calloc(count, sizeof(t_sprites))) == NULL)
		exit_when_all_good(all, 2);
	shrink_sprites_array_norm_helper(&i, &j);
	while (i < all->parser->map.s_count)
	{
		if (all->sprites[i].x != 0)
			new[j++] = all->sprites[i];
		i++;
	}
	free(all->sprites);
	all->sprites = new;
	all->parser->map.s_count = count;
}

static void		check_if_sprite(t_all *all, int i, int j, int *s_count)
{
	if (all->parser->map.map[i][j] == '+')
	{
		all->sprites[*s_count].x = j * SCALE + SCALE / 2.0;
		all->sprites[*s_count].y = i * SCALE + SCALE / 2.0;
		(*s_count)++;
	}
}

void			init_sprites(t_all *all)
{
	int i;
	int j;
	int s_count;

	s_count = 0;
	if (all->parser->map.s_count > 0)
	{
		all->sprites = ft_calloc(all->parser->map.s_count, sizeof(t_sprites));
		if (all->sprites == NULL)
			exit_when_all_good(all, 2);
		i = 0;
		while (all->parser->map.map[i] != NULL)
		{
			j = 0;
			while (all->parser->map.map[i][j] != '\0')
			{
				check_if_sprite(all, i, j, &s_count);
				j++;
			}
			i++;
		}
		shrink_spites_array(all);
	}
	else
		all->sprites = NULL;
}
