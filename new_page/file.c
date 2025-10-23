int	varname_len(char *tkn)
{
	int	len;

	len = 0;
	if (!tkn[len] || !ft_isalpha(tkn[len]) || tkn[len] != '_')
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

void	expand(t_tkn *tkn, t_env *vars, t_env *env)
{
	char	*str;
	char	*res;
	int		i;
	bool	single_q;
	bool	double_q;
	int		j;

	i = 0;
	str = tkn->token;
	res = NULL;
	single_q = false;
	double_q = false;
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[i] == '\"' && !single_q)
			double_q = !double_q;
		else if (str[i] == '$' && varname_len(&str[i + 1]))
		{
			
			res = ft_strglue(res, handle_vars(&str[i + 1]));
			if (!res)
				return (NULL); ///////////////////////////////////////////////////////leaki u errrorneri bun
			i += varname_len(&str[i + 1]) + 1;
		}
		else
		{
			j = i;
			while (str[j] && str[j] != '\'' && str[j] != '\"' && ((str[j] != '$' && j != i) || single_q))
				j++;
			tmp = ft_substr(str, i, j);
			if (!tmp)
				return (NULL);/////////////////////////////////////////////////////////nuyny stex
			res = ft_strglue(res, tmp);
			free(tmp);
			if (!res)
				return (NULL);/////////////////////////////////////////////////////////mek el stex
			i = j + 1;
		}
	}
}