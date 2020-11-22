/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:25:18 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:26:30 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *res;
	char *tmp;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	tmp = res;
	while (*s1)
	{
		*tmp = *s1;
		tmp++;
		s1++;
	}
	while (*s2)
	{
		*tmp = *s2;
		tmp++;
		s2++;
	}
	*tmp = '\0';
	return (res);
}
