/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tknprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:58:44 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/16 17:17:48 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tknprint(t_tkn *tkn_list)
{
	while (tkn_list)
	{
		printf("%s is ", tkn_list->token);
		printf("%d\n", tkn_list->type);
		tkn_list = tkn_list->next;
	}
}
