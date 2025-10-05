#include "minishell.h"

// char	*single_q(char *str)
// {
// 	int		len;
// 	char	*res;

// 	len = 0;
// 	while (str[len] != '\'')
// 		len++;
// 	if (!len)
// 		return (NULL);//
// 	res = (char *)malloc(len + 1);
// 	if (!res)
// 		return (NULL);
// }

char	*find_var(char **str, t_env *vars)
{
	int	len;

	l
	while ()
}

char	*expand_vars(char *str, t_env *vars)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, 0, i);
			if (!tmp)
				return (free(res), NULL);
			res = ft_strglue(res, tmp);
			free(tmp);
			if (!res)
				return (NULL);
			str += i;
			tmp = find_var(&str, vars);
			if (!tmp)
				return (free(res), NULL);
			res = ft_strglue(res, tmp);
			free(tmp);
			if (!res)
				return (NULL);
			i = -1;
		}
		i++;
	}
}

int	handle_arg(char *str, t_env *vars)
{
	char	*buf;
	char	*tmp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void)j;
	(void)vars;
	buf = NULL;
	tmp = NULL;
	while (str[i])
	{
		if (*str == '\'')
		{
			tmp = ft_substr(str, 0, i);
			if (!tmp)
				return (0);
			buf = ft_strglue(buf, tmp);
			free(tmp);
			if (!buf)
				return (0);
			str += i + 1;
			i = 0;
			while (str[i] && str[i] != '\'')
				i++;
			tmp = ft_substr(str, 0, i);
			if (!tmp)
				return (0);
			buf = ft_strglue(buf, tmp);
			free(tmp);
			if (!buf)
				return (0);
			str += i + 1;
			i = 0;
		}
		if (*str == '\"')
		{
			tmp = ft_substr(str, 0, i);
			if (!tmp)
				return (0);
			buf = ft_strglue(buf, tmp);
			free(tmp);
			if (!buf)
				return (0);
			str += i + 1;
			i = 0;
			while (str[i] && str[i] != '\"')
				i++;
			tmp = ft_substr(str, 0, i);
			if (!tmp)
				return (0);
			buf = ft_strglue(buf, tmp);
			free(tmp);
			if (!buf)
				return (0);
			str += i + 1;
			i = 0;
		}
		if (*str == '$')
		{
			i++;//
		}
		i++;
	}
	return (1);
}


void	expand(t_tkn *tkn, t_env *vars)
{
	int	first;

	first = 1;
	while (tkn)
	{
		if (tkn->type == ARG && !handle_arg(tkn->token, vars))
			return ; //error
		if (first && tkn->type == ARG)
		{
			tkn->type = EXEC;
			first = 0;
		}
		if (tkn->type == REDIR)
		{
			first = 1;
			if (!ft_strncmp(tkn->token, "<<", 2))
				tkn->type = HRDC;
		}
		tkn = tkn->next;
	}
}