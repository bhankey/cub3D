/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:34:52 by bhankey           #+#    #+#             */
/*   Updated: 2020/10/30 20:35:06 by bhankey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*ft_make_new_substr(char const *start, char const *end)
{
	char *substr;
	char *tmp;

	substr = (char *)malloc((end - start) + 2);
	tmp = substr;
	while (start != end)
	{
		*substr = *start;
		substr++;
		start++;
	}
	*substr = '\0';
	return (tmp);
}

static size_t	ft_count_strs(char const *s, char c)
{
	int count;

	count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		count++;
		while (*s && *s == c)
			s++;
	}
	return (count);
}

static char		**ft_clean_if_fail(char **s, size_t last_word)
{
	while (last_word > 0)
	{
		free(s[last_word--]);
	}
	free(s[0]);
	free(s);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char			**res;
	const char		*tmp;
	size_t			word_counter;
	size_t			current_word;

	if (s == NULL)
		return (NULL);
	word_counter = ft_count_strs(s, c);
	res = (char **)malloc((word_counter + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	current_word = 0;
	while (current_word < word_counter)
	{
		while (*s && *s == c)
			s++;
		tmp = s;
		while (*s && *s != c)
			s++;
		res[current_word] = ft_make_new_substr(tmp, s);
		if (res[current_word++] == NULL)
			return (ft_clean_if_fail(res, current_word - 1));
	}
	res[current_word] = NULL;
	return (res);
}
