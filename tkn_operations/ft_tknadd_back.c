/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tknadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:23:07 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/16 17:30:34 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tknadd_back(t_tkn **tkn, t_tkn *new)
{
	if (!(*tkn))
		*tkn = new;
	else
		ft_tknlast(*tkn)->next = new;
}
