

// int	crt_tkn(t_tkn **list, char *str, int *i, int *n, t_env *vars)
// {
// 	int	j;
// 	int	k;
// 	char	*buf;
// 	t_tkn	*tmp;

// 	j = 0;
// 	while (str[*i + j] && !is_whitespace(str[*i + j]))
// 	{
// 		if (str[*i + j] == '\'')
// 		{
// 			while (str[*i + j] != '\'')
// 				j++;
// 		}
// 		else if (str[*i + j] == '$')
// 			j += var_len(&str[*i + j + 1], vars);
// 		else
// 			j++;
// 	}
// 	if (str[*i + j])
// 		j++;
// 	buf = ft_substr(str, *i, j);
// 	if (!buf)
// 		return (0);
// 	buf[j - 1] = 0;
// 	tmp = ft_tknnew(buf, *n);
// 	if (!tmp)
// 		return (free(buf), 0);
// 	if (*n == EXEC)
// 		*n = ARG;
// 	else if (*n == REDIR)
// 		*n = EXEC;
// 	ft_tknadd_back(list, tmp);
// 	(*i) += j;
// 	return (1);
// }

// t_tkn *token_ape(char *str, t_env *vars)
// {
// 	// char	*buf;
// 	t_tkn	*res;
// 	// t_tkn	*tmp;
// 	int		i;
// 	int		n;

// 	i = 0;
// 	n = EXEC;
// 	res = NULL;
// 	while (str[i] && is_whitespace(str[i]))
// 			i++;
// 	while (str[i])
// 	{
// 		if (is_red(&str[i]))
// 			n = REDIR;
// 		crt_tkn(&res, str, &i, &n, vars);
// 		while (str[i] && is_whitespace(str[i]))
// 			i++;
// 	}
// 	return (res);
// }

// char	*var_handler(char *str, t_env *vars)
// {
// 	int	i;

// 	while (!is_whitespace(str[i]))
// 		i++;
// 	while (vars && ft_strncmp(vars->key, str, i) && vars->key[i])
// 		vars = vars->next;
// 	if (vars)
// 		return (vars->value);
// 	return (NULL);
// }





		// else if ((*str)[i] == '\'')
		// {
		// 	tmp = ft_substr(*str, 0, i);
		// 	if (!tmp)
		// 		return (NULL);
		// 	buf = ft_strglue(buf, tmp);
		// 	if (!buf)
		// 		return (NULL);
		// 	(*str) += i;
		// 	i = 0;
		// 	tmp = single_q(str);
		// 	if (!tmp)
		// 		return (NULL);
		// 	buf = ft_strglue(buf, tmp);
		// 	if (!buf)
		// 		return (NULL);
		// }


// // char	*ft_nexttkn(char *str, int *num)
// // {
// // 	int		i;
// // 	int		j;
// // 	char	*res;

// // 	i = 0;
// // 	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
// // 	{
// // 		(*num)++;
// // 		str++;
// // 	}
// // }





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
// 	if (!*str)
// 		return (NULL);
// 	while (str[i] && str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
// 	{
// 		(*num)++;
// 		i++;
// 	}
// 	res = (char *)malloc(i + 1);
// 	if (!res)
// 		return (NULL);
// 	res[i] = 0;
// 	j = 0;
// 	while (j < i)
// 	{
// 		// if (str[j] == '$')
// 		// {
// 		// 	res[]
// 		// }
// 		res[j] = str[j];
// 		j++;
// 	}
// 	return (res);
	

// }

// t_tkn	*tokenisation(char *str)
// {
// 	t_tkn	*res;
// 	t_tkn	*tmp;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	res = NULL;
// 	while (str[i])
// 	{
// 		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 			i++;
// 		if (str[i] == '\'')
// 		{
// 			j = 1;
// 			while (str[i + j] && str[i + j] != '\'')
// 				j++;
// 			tmp = ft_tknnew(ft_substr(str, i + 1, j - 1), 0);
// 			if (!tmp)
// 				return (NULL);
// 			ft_tknadd_back(&res, tmp);
// 			i += j + 1;
// 			continue ;
// 		}
// 		if (str[i] == '\"')
// 		{
// 			j = 1;
// 			while (str[i + j] && str[i + j] != '\"')
// 				j++;
// 			tmp = ft_tknnew(ft_substr(str, i + 1, j - 1), 0);
// 			if (!tmp)
// 				return (NULL);
// 			ft_tknadd_back(&res, tmp);
// 			i += j + 1;
// 			continue ;
// 		}
// 		tmp = ft_tknnew(ft_nexttkn(str + i, &i), 0);
// 		if (!tmp)
// 			return (NULL);
// 		ft_tknadd_back(&res, tmp);
// 	}
// 	return (res);
// }

// char	*single_q(char **str)
// {
// 	char	*res;
// 	int		i;

// 	i = 1;
// 	while ((*str)[i] && (*str)[i] != '\'')
// 		i++;
// 	if (!(*str)[i])
// 		return (NULL);
// 	res = ft_substr(*str, 0, i + 1);
// 	if (!res)
// 		return (NULL);
// 	(*str) += i;
// 	return (res);
// }

// char	*double_q(char **str)
// {
// 	char	*res;
// 	int		i;

// 	i = 1;
// 	while ((*str)[i] && (*str)[i] != '\"')
// 		i++;
// 	if (!(*str)[i])
// 		return (NULL);
// 	res = ft_substr(*str, 0, i + 1);
// 	if (!res)
// 		return (NULL);
// 	(*str) += i;
// 	return (res);
// }