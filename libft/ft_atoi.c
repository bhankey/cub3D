/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 03:06:50 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 03:13:56 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		checkstr(const char *str)
{
	int i;

	i = 0;
	if (*str == '-' || *str == '+')
	{
		str++;
		i++;
	}
	while (*str != '\0')
	{
		if (*str > '9' || *str < '0')
			return (i);
		i++;
		str++;
	}
	return (i);
}

static void		skipwhitespace(const char **str)
{
	while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\v'
	|| **str == '\f' || **str == '\r')
		(*str)++;
}

int				ft_atoi(const char *nptr)
{
	int				size;
	long long int	result;
	unsigned int	am;

	result = 0;
	am = 1;
	skipwhitespace(&nptr);
	if ((size = checkstr(nptr)) > 11 && *nptr == '-')
		return (0);
	else if ((*nptr != '-') && ((size > 11 && *nptr == '+')
	|| (size > 10 && *nptr != '+')))
		return (-1);
	while (--size >= 0)
	{
		if (nptr[size] == '-')
			result *= -1;
		else if (nptr[size] != '+')
			result += (nptr[size] - '0') * am;
		am *= 10;
	}
	if (result > 2147483647)
		return (-1);
	if (result < -2147483648)
		return (0);
	return ((int)result);
}
