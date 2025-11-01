/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tknclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 10:53:13 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/15 19:20:17 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tknclear(t_tkn **tkn)
{
	if (tkn && *tkn)
	{
		ft_tknclear(&(*tkn)->next);
		if ((*tkn)->token)
			free((*tkn)->token);
		free(*tkn);
		*tkn = NULL;
	}
	return ;
}
