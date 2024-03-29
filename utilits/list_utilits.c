/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utilits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:17:47 by bhankey           #+#    #+#             */
/*   Updated: 2020/11/22 17:17:49 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_str(void *content)
{
	char *str;

	if (content == NULL)
		return ;
	str = (char *)content;
	free(str);
}
