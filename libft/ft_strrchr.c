/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 02:59:07 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 02:59:08 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int find_char;

	find_char = -1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			find_char = i;
		i++;
	}
	if (((char)c) == '\0')
		return ((char *)(&(s[i])));
	if (find_char == -1)
		return (NULL);
	return ((char *)(&(s[find_char])));
}
