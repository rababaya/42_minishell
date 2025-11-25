#include "minishell.h"

int	check_punctuation(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (!*str)
				return (0);
		}
		else if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
				str++;
			if (!*str)
				return (0);
		}
		str++;
	}
	return (1);
}
