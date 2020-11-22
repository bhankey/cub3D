/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 02:09:55 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 02:10:19 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *res;

	res = (unsigned char *)s;
	while (n > 0)
	{
		if (*res == (unsigned char)c)
		{
			return ((void *)res);
		}
		res++;
		n--;
	}
	return (NULL);
}
