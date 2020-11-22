/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:15:43 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:17:47 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	size_t	size_str;
	char	*res;

	size_str = 0;
	while (str[size_str] != '\0')
		size_str++;
	res = (char *)malloc((size_str + 1) * sizeof(char));
	size_str = 0;
	if (res == NULL)
	{
		return (NULL);
	}
	while (str[size_str] != '\0')
	{
		res[size_str] = str[size_str];
		size_str++;
	}
	res[size_str] = '\0';
	return (res);
}
