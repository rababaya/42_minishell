/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tkniter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:56:40 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/15 17:07:09 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tkniter(t_tkn *tkn, void (*f)(void *))
{
	while (tkn && f)
	{
		f(tkn->token);
		tkn = tkn->next;
	}
	return ;
}
