/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:25:02 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/06 15:50:49 by rababaya         ###   ########.fr       */
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

// int	prepare_redirections(t_data *data, t_tkn *cmd)
// {
// 	t_tkn 	*r;
// 	int		ret;
	
// 	r = get_redir(cmd);
// 	while (r && r->type != PIPE)
// 	{
// 		if (r->type == HRDC)
// 		{
// 			ret = heredoc(data, r);
// 			if (ret == 1)
// 				return (1);
// 		}
// 		r = r->next;
// 	}
// 	return (0);
// }

// int apply_redirections(t_tkn *cmd, t_data *data)
// {
// 	t_tkn *r;
	
// 	r = get_redir(cmd);
// 	while (r && r->type != PIPE)
// 	{
// 		if (r->type == RED_OUT)
// 		{
// 			if (red_out(r))
// 				return (1);
// 		}		
// 		if (r->type == HRDC)
// 		{
// 			if (heredoc(data, r))
// 				return (1);
// 		}
// 		r = r->next;
// 	}
// 	return (0);
// }

int	redirection(t_data *data, t_tkn *cmd)
{
	t_tkn	*redir;

	(void)data;
	redir = get_redir(cmd);
	if (!redir || redir->type == PIPE)
		return (0);
	if (redir->type == HRDC)
	{
		if (redir->next && redir->next->type == ARG)
			return (heredoc(data, redir));
		return (127);
	}
	signal(SIGQUIT, SIG_DFL);
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
