/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:41:22 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:41:23 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	res = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (*s)
	{
		res[i] = (*f)(i, *s);
		i++;
		s++;
	}
	res[i] = '\0';
	return (res);
}
