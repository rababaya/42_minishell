#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13) || !c)
		return (1);
	return (0);
}

int	is_red(char *str)
{
	if (!strncmp (str, "<<", 2) && str[1] && is_whitespace(str[2]))
		return (1);
	if (!strncmp (str, ">>", 2) && str[1] && is_whitespace(str[2]))
		return (1);
	if (!strncmp (str, "<", 1) && is_whitespace(str[1]))
		return (1);
	if (!strncmp (str, ">", 1) && is_whitespace(str[1]))
		return (1);
	if (!strncmp (str, "|", 1) && is_whitespace(str[1]))
		return (1);
	if (!strncmp (str, "&&", 2) && str[1] && is_whitespace(str[2]))
		return (1);
	if (!strncmp (str, "||", 2) && str[1] && is_whitespace(str[2]))
		return (1);
	return (0);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*res;
// 	int		i;
// 	int		j;

// 	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		res[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		res[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	res[i] = 0;
// 	return (res);
// }

int	crt_tkn(t_tkn **list, char *str, int *i, int *n, t_env *vars)
{
	int	j;
	int	k;
	char	*buf;
	t_tkn	*tmp;

	j = 0;
	while (str[*i + j] && !is_whitespace(str[*i + j]))
	{
		if (str[*i + j] == '\'')
		{
			while (str[*i + j] != '\'')
				j++;
		}
		else if (str[*i + j] == '$')
			j += var_len(&str[*i + j + 1], vars);
		else
			j++;
	}
	if (str[*i + j])
		j++;
	buf = ft_substr(str, *i, j);
	if (!buf)
		return (0);
	buf[j - 1] = 0;
	tmp = ft_tknnew(buf, *n);
	if (!tmp)
		return (free(buf), 0);
	if (*n == EXEC)
		*n = ARG;
	else if (*n == REDIR)
		*n = EXEC;
	ft_tknadd_back(list, tmp);
	(*i) += j;
	return (1);
}

t_tkn *token_ape(char *str, t_env *vars)
{
	// char	*buf;
	t_tkn	*res;
	// t_tkn	*tmp;
	int		i;
	int		n;

	i = 0;
	n = EXEC;
	res = NULL;
	while (str[i] && is_whitespace(str[i]))
			i++;
	while (str[i])
	{
		if (is_red(&str[i]))
			n = REDIR;
		crt_tkn(&res, str, &i, &n, vars);
		while (str[i] && is_whitespace(str[i]))
			i++;
	}
	return (res);
}

char	*var_handler(char *str, t_env *vars)
{
	int	i;

	while (!is_whitespace(str[i]))
		i++;
	while (vars && ft_strncmp(vars->key, str, i) && vars->key[i])
		vars = vars->next;
	if (vars)
		return (vars->value);
	return (NULL);
}

char	*single_q(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (NULL);
	return (ft_substr(str, 0, i));
}

char	*double_q(char *str, t_env *vars)///////
{
	char	*res;
	char	*buf;
	int	prev;
	int	i;

	i = 0;
	prev = 0;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			buf = ft_substr(str, prev, i - prev);
			if (!buf)// add Hiroshima later
				return (NULL)
			res = ft_strjoin(res, buf);//maybe leak
			if (!res) // add Nagasaki later
				return (NULL);
			buf = var_handler(&str[i + 1], vars);
			if (buf)
			{
				res = ft_strjoin(res, buf);
				if (!res)
					return (NULL);
			}
			i += 
		}
	}
	if (!str[i])
		return (NULL);
	return (ft_substr(str, 0, i));
}



t_tkn	*nigga(char *str, t_env *vars)
{
	//char	*str;
	char	*buf;
	t_tkn	*tkn;
	int		i;
	int		j;

	while (*str)
	{
		
			
	}

}