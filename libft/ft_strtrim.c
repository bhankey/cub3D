/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:27:24 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:33:48 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_isinside(char const *s1, const char c)
{
	while (*s1)
	{
		if (*s1 == c)
			return (1);
		s1++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char		*res;
	const char	*tmp;
	int			i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (ft_isinside(set, *s1))
		s1++;
	tmp = s1;
	while (*(tmp + 1))
		tmp++;
	while (ft_isinside(set, *tmp))
		tmp--;
	res = (char *)malloc(((tmp - s1) + 2) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s1 != tmp)
		res[i++] = *(s1++);
	res[i++] = *tmp;
	res[i] = '\0';
	return (res);
}
