/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:01:24 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/06 01:37:25 by dgrigor2         ###   ########.fr       */
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

static int	handle_str(int *i, int quote, char *str, char **res)
{
	int		j;
	char	*tmp;

	j = *i;
	while (str[j] && (str[j] != '\'' || quote == 1) && (str[j] != '\"'
			|| quote == -1) && (str[j] != '$' || j == *i || quote == -1))
		j++;
	tmp = ft_substr(str, *i, j - *i);
	if (!tmp)
	{
		if (res)
			free(*res);
		return (127);
	}
	*res = ft_strglue(*res, tmp);
	free(tmp);
	if (!(*res))
		return (127);
	*i = j;
	return (0);
}

static int	handle_quotes(char c, int *quote)
{
	if (c == '\'' && *quote < 1)
	{
		if (*quote == 0)
			*quote = -1;
		else if (*quote == -1)
			*quote = 0;
		return (-1);
	}
	else if (c == '\"' && *quote > -1)
	{
		if (*quote == 0)
			*quote = 1;
		else if (*quote == 1)
			*quote = 0;
		return (1);
	}
	return (0);
}

static int	handle_vars(int *i, t_env *env, t_tkn *tkn, char **res)
{
	char	*tmp;

	tmp = find_vars(tkn->token + *i + 1, env);
	*i += varname_len(tkn->token + *i + 1) + 1;
	if (!tmp)
		return (0);
	*res = ft_strglue(*res, tmp);
	if (!*res && tmp)
		return (127);
	return (0);
}

static int	splitting(int *i, t_env *env, t_tkn *tkn, char **res)
{
	char	*var;
	char	*prev;
	t_tkn	*next;
	t_tkn	*new;
	int		j;

	j = 0;
	next = tkn->next;
	tkn->next = NULL;
	var = find_vars(tkn->token + *i + 1, env);
	*i += varname_len(tkn->token + *i + 1) + 1;
	if (!var)
		return (0);
	while (var[j])
	{
		while (var[j] && !ft_iswhitespace(var[j]))
			j++;
		prev = ft_substr(var, 0, j);
		if (!prev)
			return (127);
		*res = ft_strglue(*res, prev);
		free(prev);
		if (!*res)
			return (127);
		new = ft_tknnew(*res, ARG);
		if (!new)
			return (free(*res), 127);
		ft_tknadd_back(&tkn, new);
		*res = NULL;
		while (var[j] && ft_iswhitespace(var[j]))
			j++;
		var += j;
		j = 0;
	}
	ft_tknlast(tkn)->next = next;
	return (0);
}

int	expand(t_tkn *tkn, t_env *env)
{
	char	*res;
	int		quote;
	int		i;

	i = 0;
	quote = 0;
	res = NULL;
	while (tkn->token[i])
	{
		if (handle_quotes(tkn->token[i], &quote))
			i++;
		else if (tkn->token[i] == '$' && quote > -1
			&& varname_len(tkn->token + i + 1))
		{
			if (quote == 1 && handle_vars(&i, env, tkn, &res))
				return (127);
			else if (quote == 0 && splitting(&i, env, tkn, &res))
				return (127);
		}
		else if (handle_str(&i, quote, tkn->token, &res))
			return (127);
	}
	free(tkn->token);
	tkn->token = res;
	return (0);
}







/*
static int	calculate(char *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while(*str)
	{
		if ((*str == '\'' && !quote) || (*str == '\"' && !quote))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			len++;
		str++;
	}
	if (quote)
		return (-1);
	return (len);
}
char	*dequote(char *str)
{
	char	*res;
	int		i;
	char	quote;

	i = calculate(str);
	if (i < 0)
		return (NULL);
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
	i = 0;
	quote = 0;
	while(*str)
	{
		if ((*str == '\'' && !quote) || (*str == '\"' && !quote))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			res[i++] = *str;
		str++;
	}
	res[i] = 0;
	return (res);
}
*/