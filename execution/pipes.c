/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:27:17 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 19:40:20 by dgrigor2         ###   ########.fr       */
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

int	single_command(t_data *data, t_tkn *cmd)
{
	int	ret;

	if (redirection(data, cmd))
	{
		free_data(data);
		return (127);
	}
	if (is_builtin(cmd))
	{
		ret = builtin_call(data, cmd);
		free_data(data);
		exit(ret);
	}
	data->args = convertion(cmd, arg_len(cmd));
	if (!data->args)
		return (free_data(data), 127);
	ret = child_process(data, cmd);
	free_data(data);
	return (ret);
}

void	mayday(int *pid, int i, int fd[2], int len)
{
	int	j;

	j = 0;
	if (i != len)
	{
		close(fd[0]);
		close(fd[1]);
	}
	while (j < i)
	{
		waitpid(pid[j], NULL, 0);
		j++;
	}
}

int	pipes(t_data *data, t_tkn *tkn)
{
	int	fd[2];
	int	*pid;
	int	len;
	int	lastread;
	int	i;

	i = 0;
	lastread = 0;
	len = pipe_count(tkn);
	pid = (int *)malloc(sizeof(int) * (len + 1));
	if (!pid)
		return (127);
	while (i <= len)
	{
		if (i != len && pipe(fd))
		{
			mayday(pid, i, fd, i);
			return (127);
		}
		pid[i] = fork();
		if (pid[i] < 0)
		{
			mayday(pid, i, fd, len);
			return (127);
		}
		if (pid[i] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			free(pid);
			close_unused_heredocs(data, tkn);
			if (i != len)
				close(fd[0]);
			if (i)
			{
				dup2(lastread, STDIN_FILENO);
				close(lastread);
			}
			if (i != len)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			exit(single_command(data, tkn));
		}
		if (i != len)
			close(fd[1]);
		if (i)
			close(lastread);
		if (i != len)
			lastread = fd[0];
		i++;
		tkn = next_pipe(tkn);
		if (tkn)
			tkn = tkn->next;
	}
	(void)data;
	i = 0;
	while (i < len)
	{
		waitpid(pid[i++], NULL, 0);
	}
	waitpid(pid[i], &data->exit_status, 0);
	free(pid);
	return (data->exit_status);
}
