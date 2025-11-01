/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tkndelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:18 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/11/01 17:07:29 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tkndelone(t_tkn **lst, t_tkn *tkn)
{
	t_tkn	*tmp;

	if (lst && tkn)
	{
		tmp = *lst;
		if (tmp == tkn)
		{
			*lst = (*lst)->next;
			free(tkn->token);
			free(tkn);
			return ;
		}
		while (tmp->next && tmp->next != tkn)
			tmp = tmp->next;
		tmp->next = tkn->next;
		free(tkn->token);
		free(tkn);
	}
}
