/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 02:53:11 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 02:54:26 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t j;
	size_t i;
	size_t dst_s;

	j = ft_strlen(dst);
	dst_s = j;
	i = 0;
	while (src[i] != '\0' && j + 1 < size)
	{
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	if (size < dst_s)
	{
		return (ft_strlen(src) + size);
	}
	else
		return (ft_strlen(src) + dst_s);
}
