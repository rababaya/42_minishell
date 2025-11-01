/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tknsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:37:32 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/15 16:52:58 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tknsize(t_tkn *tkn)
{
	int	i;
	int	empties;

	empties = 0;
	i = 0;
	while (tkn)
	{
		i++;
		if (!tkn->token)
			empties++;
		tkn = tkn->next;
	}
	return (i - empties);
}
