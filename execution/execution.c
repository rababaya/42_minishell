/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:01:00 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/17 18:25:10 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_direct_path(char *cmd, char **path)
{
	int	ret;

	if (cmd[0] == '.' || cmd[0] == '/')
	{
		ret = is_valid_exec(cmd);
		if (ret)
			return (ret);
		*path = cmd;
		return (0);
	}
	return (-1);
}

static int	search_in_paths(char *cmd, char **paths, char **path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		if (path_join(cmd, paths[i], &tmp))
			return (free_split(&paths), 1);
		if (!access(tmp, F_OK) && !access(tmp, X_OK))
		{
			*path = tmp;
			return (free_split(&paths), 0);
		}
		free(tmp);
		i++;
	}
	return (free_split(&paths), 127);
}

int	set_to_path(t_env *env, char *cmd, char **path)
{
	char	**paths;
	int		ret;

	if (!cmd)
		return (1);
	ret = check_direct_path(cmd, path);
	if (ret != -1)
		return (ret);
	if (get_path(env))
		paths = ft_split(get_path(env), ':');
	else
		return (127);
	if (!paths)
		return (1);
	return (search_in_paths(cmd, paths, path));
}

int	builtin_call(t_data *data, t_tkn *cmd)
{
	int	redtype;
	int	fd[2];
	int	ret;

	redtype = red_in_out(cmd);
	if (redtype == 1 || redtype == 3)
		fd[1] = dup(STDOUT_FILENO);
	if (redtype == 2 || redtype == 3)
		fd[0] = dup(STDIN_FILENO);
	ret = redirection(data, cmd);
	if (ret)
		return (ret);
	data->args = convertion(cmd, arg_len(cmd));
	if (!data->args)
		return (1);
	data->exit_status = call(data);
	if ((redtype == 1 || redtype == 3) && dup2(fd[1], STDOUT_FILENO) < 0)
		return (close(fd[1]), errno);
	if ((redtype == 2 || redtype == 3) && dup2(fd[0], STDIN_FILENO) < 0)
		return (close(fd[0]), errno);
	if (redtype == 1 || redtype == 3)
		close(fd[1]);
	if (redtype == 2 || redtype == 3)
		close(fd[0]);
	return (0);
}

int	execution(t_data *data, t_tkn *cmd)
{
	int	ret;

	ret = open_heredocs(data);
	setup_prompt_signals();
	if (data->exit_status == -1)
	{
		data->exit_status = 0;
		return (0);
	}
	if (ret)
		return (1);
	if (!next_pipe(cmd))
	{
		if (is_builtin(data->tkn_list))
			return (builtin_call(data, cmd));
		else
			ret = no_pipes(data, cmd);
	}
	else
		ret = pipes(data, cmd);
	if (WIFEXITED(ret))
		data->exit_status = WEXITSTATUS(ret);
	if (WIFSIGNALED(ret))
		data->exit_status = WTERMSIG(ret) + 128;
	return (0);
}
