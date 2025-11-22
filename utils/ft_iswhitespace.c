#include "minishell.h"

int	ft_iswhitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13) || !c)
		return (1);
	return (0);
}