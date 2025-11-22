/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:05 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/11/22 20:07:57 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13) || !c)
		return (1);
	return (0);
}

int	is_red(char *str)
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

t_tkn	*tkn_red(char **str)
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

t_tkn	*tkn_arg(char **str)
{
	t_tkn	*res;
	char	*buf;
	int		i;

	i = 0;
	while ((*str)[i] && !is_whitespace((*str)[i]) && !is_red(&(*str)[i]))
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
	buf = ft_substr(*str, 0, i);
	if (!buf)
		return (NULL);
	(*str) += i;
	res = ft_tknnew(buf, ARG);
	if (!res)
		free(buf);
	return (res);
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
		else if (is_whitespace(*str))
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

// t_tkn	*tokenise(char *str)
// {
// 	t_tkn	*buf;
// 	t_tkn	*res;

// 	res = NULL;
// 	if (!str)
// 		return (NULL);
// 	while (*str)
// 	{
// 		if (is_red(str))
// 		{
// 			buf = tkn_red(&str);
// 			if (!buf)
// 				return (ft_tknclear(&res), NULL);
// 			ft_tknadd_back(&res, buf);
// 		}
// 		else if (is_whitespace(*str))
// 			str++;
// 		else
// 		{
// 			buf = tkn_arg(&str);
// 			if (!buf)
// 				return (ft_tknclear(&res), NULL);
// 			ft_tknadd_back(&res, buf);
// 		}
// 	}
// 	return (res);
// }
