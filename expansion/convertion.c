#include "minishell.h"

char	**convertion(t_tkn *tkn)
{
	char	**res;
	int		len;
	int		i;

	len = ft_tknsize(tkn);
	if (!len) /////////////
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (tkn)
	{
		if (tkn->token)
		{
			res[i] = tkn->token;
			i++;
		}
		tkn = tkn->next;
	}
	res[i] = NULL;
	return (res);
}