/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:41:56 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:42:04 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int		ft_get_size(int n)
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

void			ft_putnbr_fd(int n, int fd)
{
	char			res[12];
	int				size;
	long long int	nn;

	if (n == 0)
		write(fd, "0", 1);
	size = ft_get_size(n);
	nn = n;
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
	ft_putstr_fd(res, fd);
}
