/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:02:02 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/11 16:02:43 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varname_len(char *tkn)
{
	int	len;

	len = 0;
	if (!tkn[len] || (!ft_isalpha(tkn[len]) && tkn[len] != '_'))
		return (0);
	while (tkn[len] && (ft_isalnum(tkn[len]) || tkn[len] == '_'))
		len++;
	return (len);
}

char	*find_vars(char *tkn, t_env *env)
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

int	handle_str(int *i, int quote, char *str, char **res)
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

int	handle_quotes(char c, int *quote)
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

int	handle_vars(int *i, t_env *env, t_tkn *tkn, char **res)
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
