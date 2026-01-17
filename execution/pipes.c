/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:27:17 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 18:14:26 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	in_child(t_pipes *p, t_data *data, t_tkn *tkn)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	free(p->pid);
	close_unused_heredocs(data, tkn);
	if (p->i)
	{
		dup2(p->lastread, STDIN_FILENO);
		close(p->lastread);
	}
	if (p->i != p->len)
	{
		dup2((p->fd)[1], STDOUT_FILENO);
		close((p->fd)[1]);
		close((p->fd)[0]);
	}
	exit(single_command(data, tkn));
}

t_tkn	*normi_xatr(t_pipes *p, t_tkn *tkn)
{
	if (p->i != p->len)
		close((p->fd)[1]);
	if (p->i)
		close(p->lastread);
	if (p->i != p->len)
		p->lastread = (p->fd)[0];
	(p->i)++;
	tkn = next_pipe(tkn);
	if (tkn)
		tkn = tkn->next;
	return (tkn);
}

int	pipes(t_data *data, t_tkn *tkn)
{
	t_pipes	p;

	p.i = 0;
	p.lastread = 0;
	p.len = pipe_count(tkn);
	p.pid = (int *)malloc(sizeof(int) * (p.len + 1));
	if (!p.pid)
		return (127);
	while (p.i <= p.len)
	{
		if (p.i != p.len && pipe(p.fd))
			return (mayday(p.pid, p.i, p.fd, p.i), 127);
		(p.pid)[p.i] = fork();
		if ((p.pid)[p.i] < 0)
			return (mayday(p.pid, p.i, p.fd, p.len), 127);
		if ((p.pid)[p.i] == 0)
			in_child(&p, data, tkn);
		tkn = normi_xatr(&p, tkn);
	}
	p.i = 0;
	while (p.i < p.len)
		waitpid((p.pid)[(p.i)++], NULL, 0);
	waitpid((p.pid)[p.i], &data->exit_status, 0);
	return (free(p.pid), data->exit_status);
}
