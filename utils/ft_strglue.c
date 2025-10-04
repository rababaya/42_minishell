#include "minishell.h"

char	*ft_strglue(char *s1, char *s2)
{
	char	*res;
	char	*start;

	if (!s1)
		return (s2);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	start = res;
	if (s1)
		while (*s1)
			*(res++) = *(s1++);
	if (s2)
		while (*s2)
			*(res++) = *(s2++);
	*res = '\0';
	free(s1);
	return (start);
}