/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:07:29 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/11 16:08:59 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red(char *str)
{
	if (!strncmp (str, "<<", 2))
		return (2);
	if (!strncmp (str, ">>", 2))
		return (2);
	if (*str == '<')
		return (1);
	if (*str == '>')
		return (1);
	if (*str == '|')
		return (1);
	return (0);
}

int	red_type(char *str)
{
	if (!strncmp (str, "<<", 2))
		return (HRDC);
	if (!strncmp (str, ">>", 2))
		return (APPND);
	if (*str == '<')
		return (RED_IN);
	if (*str == '>')
		return (RED_OUT);
	if (*str == '|')
		return (PIPE);
	return (0);
}

t_tkn	*tkn_red(char **str)
{
	char	*tmp;
	t_tkn	*res;

	tmp = ft_substr(*str, 0, is_red(*str));
	if (!tmp)
		return (NULL);
	res = ft_tknnew(tmp, red_type(*str));
	(*str) += is_red(*str);
	if (!res)
		free(tmp);
	return (res);
}

t_tkn	*crt_tkn(char **str, int i)
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

t_tkn	*tkn_arg(char **str)
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
