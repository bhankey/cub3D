/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:19:37 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:24:28 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	char	*ft_emptystring(void)
{
	return (ft_strdup(""));
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*tmp;

	if (s == NULL)
		return (NULL);
	if ((size_t)start > (size_t)ft_strlen(s))
		return (ft_emptystring());
	res = (char *)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	tmp = res;
	s += start;
	while (*s && len != 0)
	{
		*tmp = *s;
		tmp++;
		s++;
		len--;
	}
	*tmp = '\0';
	return (res);
}
