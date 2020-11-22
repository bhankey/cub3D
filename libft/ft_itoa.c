/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:39:43 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:39:44 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	get_size(int n)
{
	int size;

	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*zero_case(void)
{
	char *res;

	res = (char *)malloc(2 * sizeof(char));
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

char		*ft_itoa(int n)
{
	char			*res;
	int				size;
	long long int	nn;

	if (n == 0)
		return (zero_case());
	size = get_size(n);
	nn = n;
	res = (char *)malloc((size + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[size] = '\0';
	if (nn < 0)
	{
		*res = '-';
		nn *= -1;
	}
	while (nn)
	{
		res[--size] = '0' + (nn % 10);
		nn /= 10;
	}
	return (res);
}
