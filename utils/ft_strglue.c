#include "minishell.h"

char	*ft_strglue(char *s1, char *s2)
{
	char	*res;
	char	*start;
	char	*s1_cpy;

	s1_cpy = s1;
	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (free(s1), NULL);
	start = res;
	while (*s1)
		*(res++) = *(s1++);
	while (*s2)
			*(res++) = *(s2++);
	*res = 0;
	free(s1_cpy);
	return (start);
}