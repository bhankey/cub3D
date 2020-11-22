/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 03:05:08 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 03:05:10 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t len_little;

	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && (int)i <= (int)len - (int)len_little)
	{
		if (ft_strncmp(&big[i], little, len_little) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
