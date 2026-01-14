/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:25:02 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/14 14:43:00 by rababaya         ###   ########.fr       */
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
	
	fd = open(cmd->next->token, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		return (127);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (127);
	close(fd);
	return (0);
}

int	appnd(t_tkn *cmd)
{
	int		fd;
	
	fd = open(cmd->next->token, O_WRONLY | O_TRUNC | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (127);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (127);
	close(fd);
	return (0);
}

int	red_in(t_tkn *cmd)
{
	int		fd;
	
	if (access(cmd->next->token, F_OK))
		return (127);
	if (access(cmd->next->token, R_OK))
		return (126);
	fd = open(cmd->next->token, O_RDONLY);
	if (fd < 0)
		return (127);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (127);
	close(fd);
	return (0);
}

// void	cut_reds(t_data *data, t_tkn **cmd)
// {
// 	t_tkn *tmp;

// 	if (data->tkn_list == *cmd)
// 	{
// 		data->tkn_list = (*cmd)->next->next;
// 		free((*cmd)->next->token);
// 		free((*cmd)->next);
// 		free((*cmd)->token);
// 		free((*cmd));
// 		*cmd = data->tkn_list;
// 		return ;
// 	}
// 	tmp = data->tkn_list;
// 	while (tmp && tmp->next != *cmd)
// 		tmp = tmp->next;
	
	
// }

int	redirection (t_data *data, t_tkn *cmd)
{
	t_tkn	*redir;

	redir = get_redir(cmd);
	while (redir && redir->type != PIPE)
	{
		if (redir->type == HRDC)
		{
			if (heredoc(data, redir))
				return (1);
		}
		else if (redir->type == RED_OUT)
		{
			if (red_out(redir))
				return (1);
		}
		else if (redir->type == RED_IN)
		{
			if (red_in(redir))
				return (1);
		}
		else if (redir->type == APPND)
		{
			if (appnd(redir))
				return (1);
		}
		redir = redir->next;
	}
	signal(SIGQUIT, SIG_DFL);
	if (heredoc_execution(data))
		return (1);
	return (0);
}
