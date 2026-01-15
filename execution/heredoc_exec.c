/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:15:35 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/15 21:15:44 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn	*get_last_tkn(t_tkn *tkn)
{
	while (tkn && tkn->type != PIPE)
		tkn = tkn->next;
	return (tkn);
}

int	is_last_hrdc(t_tkn *tkn)
{
	tkn = tkn->next;
	while (tkn && tkn->type != PIPE)
	{
		if (tkn->type == HRDC)
			return (0);
		tkn = tkn->next;
	}
	return (1);
}

int	get_proper_fd(t_data *data, t_tkn *tkn)
{
	int		i;
	t_tkn	*last;

	i = 0;
	last = get_last_tkn(tkn);
	while ((data->hrdc)[i].tkn != last)
		i++;
	return ((data->hrdc)[i].fd);
}

int	heredoc_execution(t_data *data, t_tkn *tkn)
{
	int	fd;

	if (!is_last_hrdc(tkn))
		return (0);
	fd = get_proper_fd(data, tkn);
	if (fd == 0)
		return (0);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), errno);
	close(fd);
	return (0);
}
