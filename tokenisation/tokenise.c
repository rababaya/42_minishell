#include "minishell.h"

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
		res[j] = str[j];
		j++;
	}
	return (res);
	

}

t_env	*tokenisation(char *str)
{
	t_env	*res;
	t_env	*tmp;
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
			tmp = ft_envnew(ft_substr(str, i + 1, j - 1), NULL);
			if (!tmp)
				return (NULL);
			ft_envadd_back(&res, tmp);
			i += j + 1;
			continue ;
		}
		if (str[i] == '\"')
		{
			j = 1;
			while (str[i + j] && str[i + j] != '\"')
				j++;
			tmp = ft_envnew(ft_substr(str, i + 1, j - 1), NULL);
			if (!tmp)
				return (NULL);
			ft_envadd_back(&res, tmp);
			i += j + 1;
			continue ;
		}
		tmp = ft_envnew(ft_nexttkn(str + i, &i), NULL);
		if (!tmp)
			return (NULL);
		ft_envadd_back(&res, tmp);
	}
	return (res);
}