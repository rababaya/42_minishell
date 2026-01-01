/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:00:13 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/12/20 15:38:25 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convertion(t_tkn *tkn, int len)
{
	char	**res;
	int		i;

	if (len < 0)
		len = ft_tknsize(tkn);
	if (!len) /////////////
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (tkn && i < len)
	{
		if (tkn->token)
		{
			res[i] = tkn->token;
			i++;
		}
		tkn = tkn->next;
	}
	res[i] = NULL;
	return (res);
}
