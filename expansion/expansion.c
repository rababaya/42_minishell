/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:01:24 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/14 13:52:52 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	varname_len(char *tkn)
{
	int	len;

	len = 0;
	if (tkn[len] == '?')
		return (1);
	if (!tkn[len] || (!ft_isalpha(tkn[len]) && tkn[len] != '_'))
		return (0);
	while (tkn[len] && (ft_isalnum(tkn[len]) || tkn[len] == '_'))
		len++;
	return (len);
}

static char	*find_vars(char *tkn, t_data *data)
{
	int	len;
	t_env	*env;

	env = data->env_list;
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

static int	handle_vars(int *i, t_data *data, t_tkn *tkn, char **res)
{
	char	*tmp;
	int		free_tmp;

	free_tmp = 0;
	if (*(tkn->token + *i + 1) == '?')
	{
		tmp = ft_itoa(data->exit_status);
		if (!tmp)
			return (1);
		free_tmp = 1;
	}
	else
		tmp = find_vars(tkn->token + *i + 1, data);
	*i += varname_len(tkn->token + *i + 1) + 1;
	if (!tmp)
		return (0);
	*res = ft_strglue(*res, tmp);
	if (free_tmp)
		free(tmp);
	if (!*res)
		return (1);
	return (0);
}

int	expand(t_tkn *tkn, t_data *data)
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
			if (quote != -1 && handle_vars(&i, data, tkn, &res))
				return (1);
		}
		else if (handle_str(&i, quote, tkn->token, &res))
			return (1);
	}
	free(tkn->token);
	tkn->token = res;
	return (0);
}
