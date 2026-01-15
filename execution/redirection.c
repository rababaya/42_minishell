/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:25:02 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/15 14:41:04 by dgrigor2         ###   ########.fr       */
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
		return (errno);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (errno);
	close(fd);
	return (0);
}

int	appnd(t_tkn *cmd)
{
	int		fd;
	
	fd = open(cmd->next->token, O_WRONLY | O_TRUNC | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (errno);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (errno);
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
		return (errno);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (errno);
	close(fd);
	return (0);
}

int	redirection (t_data *data, t_tkn *cmd)
{
	t_tkn	*redir;
	int		ret;

	ret = 0;
	redir = get_redir(cmd);
	while (redir && redir->type != PIPE)
	{
		if (redir->type == HRDC)
			ret = heredoc_execution(data, redir);
		else if (redir->type == RED_OUT)
			ret = red_out(redir);
		else if (redir->type == RED_IN)
			ret = red_in(redir);
		else if (redir->type == APPND)
			ret = appnd(redir);
		if (ret)
			return (ret);
		redir = redir->next;
	}
	signal(SIGQUIT, SIG_DFL);
	return (0);
}
