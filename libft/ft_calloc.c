/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:07:08 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:07:22 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;
	size_t			size_mem;

	size_mem = nmemb * size;
	res = (unsigned char *)malloc(size_mem);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, size_mem);
	return (res);
}
