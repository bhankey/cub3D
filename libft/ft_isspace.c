
#include "libft.h"

int ft_isspace(int ch)
{
	if (ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r' ||
	ch == ' ')
		return (1);
	return (0);
}