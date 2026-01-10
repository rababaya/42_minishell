/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:00:13 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/10 16:44:45 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_len(t_tkn *tkn)
{
	int	i;

	i = 0;
	while (tkn && tkn->type != PIPE)
	{
		if (tkn->type == HRDC)
		{
			tkn = tkn->next->next;
			continue ;
		}
		i++;
		tkn = tkn->next;
	}
	return (i);
}

char	**convertion(t_tkn *tkn, int len)
{
	char	**res;
	int		i;

	if (len < 0)
		len = arg_len(tkn);
	if (!len)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (tkn && i < len)
	{
		if (tkn->type == HRDC)
		{
			tkn = tkn->next->next;
			continue ;
		}
		res[i] = tkn->token;
		i++;
		tkn = tkn->next;
	}
	res[i] = NULL;
	return (res);
}
