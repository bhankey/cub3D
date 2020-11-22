/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 02:45:43 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 02:47:24 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int len;

	if (src == NULL || dst == NULL)
		return (0);
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (--size && *src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (len);
}
