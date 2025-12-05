/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:40:24 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/11/25 13:40:35 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_empties(t_tkn **tkn)
{
	t_tkn	*tmp;
	t_tkn	*scnd;

	tmp = *tkn;
	while (tmp && !(tmp->token))
	{
		*tkn = tmp->next;
		free(tmp);
		tmp = *tkn;
	}
	while (tmp && tmp->next)
	{
		if (!(tmp->next->token))
		{
			scnd = tmp->next->next;
			free(tmp->next);
			tmp->next = scnd;
		}
		else
		{
			tmp = tmp->next;
		}
	}
}
