#include "minishell.h"


// char	*ft_nexttkn(char *str, int *num)
// {
// 	int		i;
// 	int		j;
// 	char	*res;

// 	i = 0;
// 	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
// 	{
// 		(*num)++;
// 		str++;
// 	}
// }





char	*ft_nexttkn(char *str, int *num)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
	{
		(*num)++;
		str++;
	}
	if (!*str)
		return (NULL);
	while (str[i] && str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
	{
		(*num)++;
		i++;
	}
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
	res[i] = 0;
	j = 0;
	while (j < i)
	{
		// if (str[j] == '$')
		// {
		// 	res[]
		// }
		res[j] = str[j];
		j++;
	}
	return (res);
	

}

t_tkn	*tokenisation(char *str)
{
	t_tkn	*res;
	t_tkn	*tmp;
	int		i;
	int		j;

	i = 0;
	res = NULL;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '\'')
		{
			j = 1;
			while (str[i + j] && str[i + j] != '\'')
				j++;
			tmp = ft_tknnew(ft_substr(str, i + 1, j - 1), 0);
			if (!tmp)
				return (NULL);
			ft_tknadd_back(&res, tmp);
			i += j + 1;
			continue ;
		}
		if (str[i] == '\"')
		{
			j = 1;
			while (str[i + j] && str[i + j] != '\"')
				j++;
			tmp = ft_tknnew(ft_substr(str, i + 1, j - 1), 0);
			if (!tmp)
				return (NULL);
			ft_tknadd_back(&res, tmp);
			i += j + 1;
			continue ;
		}
		tmp = ft_tknnew(ft_nexttkn(str + i, &i), 0);
		if (!tmp)
			return (NULL);
		ft_tknadd_back(&res, tmp);
	}
	return (res);
}
