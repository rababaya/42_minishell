/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:25:02 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/12/20 15:37:19 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn	*get_redir(t_tkn *cmd)
{
	while (cmd && cmd->type == ARG)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

int	red_out(t_tkn *cmd)
{
	int		fd;
	fd = open(get_redir(cmd)->next->token, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (127);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (127);
	close(fd);
	return (0);
}

int	redirection(t_data *data, t_tkn *cmd)
{
	t_tkn	*redir;

	(void)data;
	redir = get_redir(cmd);
	if (!redir || redir->type == PIPE)
		return (0);
	if (redir->type == RED_OUT)
	{
		if (redir->next && redir->next->type == ARG)
			return (red_out(cmd));
		return (127);
	}
	return (127);
	// if (redir->type == RED_IN)
	// {
		
	// }
}



