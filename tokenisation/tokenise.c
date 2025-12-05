/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:05 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/11/25 13:49:35 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_red(char *str)
{
	if (!strncmp (str, "<<", 2))
		return (2);
	if (!strncmp (str, ">>", 2))
		return (2);
	if (!strncmp (str, "&&", 2))
		return (2);
	if (!strncmp (str, "||", 2))
		return (2);
	if (*str == '<')
		return (1);
	if (*str == '>')
		return (1);
	if (*str == '|')
		return (1);
	return (0);
}

static t_tkn	*tkn_red(char **str)
{
	char	*tmp;
	t_tkn	*res;

	tmp = ft_substr(*str, 0, is_red(*str));
	if (!tmp)
		return (NULL);
	(*str) += is_red(*str);
	res = ft_tknnew(tmp, REDIR);
	if (!res)
		free(tmp);
	return (res);
}

static t_tkn	*crt_tkn(char **str, int i)
{
	char	*buf;
	t_tkn	*res;

	buf = ft_substr(*str, 0, i);
	if (!buf)
		return (NULL);
	(*str) += i;
	res = ft_tknnew(buf, ARG);
	if (!res)
		free(buf);
	return (res);
}

static t_tkn	*tkn_arg(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i] && !ft_iswhitespace((*str)[i]) && !is_red(&(*str)[i]))
	{
		if ((*str)[i] == '\"')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\"')
				i++;
			if (!(*str)[i])
				return (NULL); //add error message later
		}
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\'')
				i++;
			if (!(*str)[i])
				return (NULL); //add error message later
		}
		i++;
	}
	return (crt_tkn(str, i));
}

int	tokenise(t_tkn **tkn, char *str)
{
	t_tkn	*buf;

	while (*str)
	{
		if (is_red(str))
		{
			buf = tkn_red(&str);
			if (!buf)
				return (ft_tknclear(tkn), -1);
			ft_tknadd_back(tkn, buf);
		}
		else if (ft_iswhitespace(*str))
			str++;
		else
		{
			buf = tkn_arg(&str);
			if (!buf)
				return (ft_tknclear(tkn), -1);
			ft_tknadd_back(tkn, buf);
		}
	}
	return (0);
}
