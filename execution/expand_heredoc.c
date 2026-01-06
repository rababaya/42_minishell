/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:01:24 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/06 17:21:21 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	varname_len(char *tkn)
{
	int	len;

	len = 0;
	if (!tkn[len] || (!ft_isalpha(tkn[len]) && tkn[len] != '_'))
		return (0);
	while (tkn[len] && (ft_isalnum(tkn[len]) || tkn[len] == '_'))
		len++;
	return (len);
}

static char	*find_vars(char *tkn, t_env *env)
{
	int	len;

	len = varname_len(tkn);
	while (env)
	{
		if (!ft_strncmp(tkn, env->key, len))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	handle_str(int *i, char *str, char **res)
{
	int		j;
	char	*tmp;

	j = *i;
	while (str[j] && (str[j] != '$' || j == *i))
		j++;
	tmp = ft_substr(str, *i, j - *i);
	if (!tmp)
	{
		if (res)
			free(*res);
		return (1);
	}
	*res = ft_strglue(*res, tmp);
	free(tmp);
	if (!(*res))
		return (1);
	*i = j;
	return (0);
}

static int	handle_vars(int *i, t_env *env, char **line, char **res)
{
	char	*tmp;

	tmp = find_vars(*line + *i + 1, env);
	*i += varname_len(*line + *i + 1) + 1;
	if (!tmp)
		return (0);
	*res = ft_strglue(*res, tmp);
	if (!*res && tmp)
		return (127);
	return (0);
}

int	expand_heredoc(char **line, t_env *env)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && varname_len(*line + i + 1))
		{
			if (handle_vars(&i, env, line, &res))
				return (127);
		}
		else if (handle_str(&i, *line, &res))
			return (127);
	}
	free(*line);
	*line = res;
	return (0);
}
