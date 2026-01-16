/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   punctuation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:05:50 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/16 18:06:08 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_punctuation(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (!*str)
				return (0);
		}
		else if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
				str++;
			if (!*str)
				return (0);
		}
		str++;
	}
	return (1);
}

int	syntax_check(t_tkn *tkn)
{
	if (tkn->type == PIPE)
		return (2);
	while (tkn)
	{
		if (tkn->type == PIPE && tkn->next && tkn->next->type != PIPE)
		{
			tkn = tkn->next;
			continue ;
		}
		if (tkn->type != ARG && (!tkn->next || tkn->next->type != ARG))
			return (2);
		tkn = tkn->next;
	}
	return (0);
}
