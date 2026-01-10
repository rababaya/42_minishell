/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tknprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:58:44 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/10 16:44:32 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tknprint(t_tkn *tkn_list)
{
	char	*type[] = {"Argument", "Output redirection", "Input redirection", "Output append", "Pipe", "Heredoc", NULL};
	
	while (tkn_list)
	{
		printf("%s is ", tkn_list->token);
		printf("%s\n", type[tkn_list->type]);
		tkn_list = tkn_list->next;
	}
}
