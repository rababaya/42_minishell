/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:12:29 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 18:12:38 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn	*next_pipe(t_tkn *tkn)
{
	while (tkn && tkn->type != PIPE)
	{
		tkn = tkn->next;
	}
	return (tkn);
}

int	pipe_count(t_tkn *tkn)
{
	int	c;

	c = 0;
	while (tkn)
	{
		if (tkn->type == PIPE)
		{
			c++;
		}
		tkn = tkn->next;
	}
	return (c);
}

int	next_pipe_count(t_tkn *tkn)
{
	int	count;

	count = 0;
	while (tkn && tkn->type != PIPE)
	{
		count++;
		tkn = tkn->next;
	}
	return (count);
}
