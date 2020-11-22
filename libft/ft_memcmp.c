/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 02:11:07 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:55:34 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *first;
	unsigned char *second;

	first = (unsigned char *)s1;
	second = (unsigned char *)s2;
	while (n > 0)
	{
		if (*first != *second)
			return ((int)(*first) - (int)(*second));
		n--;
		first++;
		second++;
	}
	return (0);
}
