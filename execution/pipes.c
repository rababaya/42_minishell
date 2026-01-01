#include "minishell.h"

t_tkn	*next_pipe(t_tkn *tkn)
{
	while (tkn && tkn->type != PIPE)
	{
		tkn = tkn->next;
	}
	return (tkn);
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
	int		ret;

	if (redirection(data, cmd))
	{
		return (127);
	}
	ret = call(data);
	if (call != 2)
	{
		child_process(data, cmd);
		///
	}
	return (ret);
}

int	pipes(t_data *data, t_tkn *tkn)
{
	int	fd[2];
	int	pid;
	int	status;
	t_tkn	*next;

	next = next_pipe(tkn);
	if (!next)
	{
		single_command(data, tkn);
		////
	}

	if (pipe(fd) < 0)
		return (127);
	pid = fork();
	if (pid < 0)
		return (127);
	if (pid == 0)
	{
		dup2(fd[1], STDIN_FILENO);
		pipes (data, next->next);
	}
	else
	{
		dup2(fd[0], STDOUT_FILENO);
		single_command(data, tkn);
		////
	}
	return (0);
}