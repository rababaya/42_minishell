/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:01:24 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/11 16:02:29 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
