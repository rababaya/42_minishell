/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:45:00 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 19:31:07 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(t_data *data, t_tkn *cmd)
{
	char	*path;
	char	**envp;
	char	**args;
	int		ret;

	path = NULL;
	if (!get_cmd(cmd))
		return (0);
	envp = lst_to_str(data->env_list);
	if (!envp)
		return (1);
	ret = set_to_path(data->env_list, get_cmd(cmd), &path);
	if (ret)
	{
		if (path)
			free(path);
		return (print_err(cmd->token), free_split(&envp), ret);
	}
	args = convertion(cmd, arg_len(cmd));
	if (!args)
		return (free(path), free_split(&envp), 1);
	cleanup(&data, args);
	execve(path, args, envp);
	return (free_split(&args), free_split(&envp), 2);
}

int	no_pipes(t_data *data, t_tkn *cmd)
{
	int	pid;
	int	ret;

	pid = fork();
	if (pid < 0)
		return (perror("minishell"), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close_unused_heredocs(data, cmd);
		ret = redirection(data, cmd);
		if (ret)
		{
			free_data(data);
			write(2, "Redirection error\n", 18);
			exit(ret);
		}
		ret = child_process(data, cmd);
		if (ret != 2)
			free_data(data);
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	return (ret);
}
