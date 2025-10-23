#include "minishell.h"

int	varname_len(char *tkn)
{
	int	len;

	len = 0;
	if (!tkn[len] || !ft_isalpha(tkn[len]) || tkn[len] == '_')
		return (1);
	while (tkn[len] && (ft_isalnum(tkn[len]) || tkn[len] == '_'))
		len++;
	return (len);
}

char	*handle_vars(char *tkn, t_env *vars, t_env *env)
{
	int	len;

	len = varname_len(tkn);
	while (env)
	{
		if (!ft_strncmp(tkn, env->key, len))
			return (env->value);
		env = env->next;
	}
	while (vars)
	{
		if (!ft_strncmp(tkn, vars->key, len))
			return (vars->value);
		vars = vars->next;
	}
	return (NULL);
}

int	expand(t_tkn *tkn, t_env *vars, t_env *env)
{
	char	*str;
	char	*res;
	char	*tmp;
	int		i;
	bool	single_q;
	bool	double_q;
	int		j;

	if (!tkn)
		return (0);
	i = 0;
	str = tkn->token;
	res = NULL;
	single_q = false;
	double_q = false;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
		{
			single_q = !single_q;
			i++;
		}
		else if (str[i] == '\"' && !single_q)
		{
			i++;
			double_q = !double_q;
		}
		else if (str[i] == '$' && !single_q && varname_len(str + i + 1))
		{
			res = ft_strglue(res, handle_vars(str + i + 1, vars, env));
			if (!res)
				return (127);
			i += varname_len(str + i + 1) + 1;
		}
		else
		{
			j = i;
			while (str[j] && (str[j] != '\'' || double_q) && (str[j] != '\"' || single_q) && (str[j] != '$' || j == i || single_q))// str[j], str[j] isn't ' or inside ", str[j] isn't " or inside ', str[j] isn't $ or j == i or inside '
				j++;
			tmp = ft_substr(str, i, j - i);
			if (!tmp)
			{
				if (res)
					free(res);
				return (127);
			}
			res = ft_strglue(res, tmp);
			free(tmp);
			if (!res)
				return (127);
			i = j;
		}
	}
	free(str);
	tkn->token = res;
	return (0);
}