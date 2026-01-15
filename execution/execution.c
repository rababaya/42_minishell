/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:01:00 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/15 22:10:12 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(t_tkn *cmd)
{
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type != ARG)
			cmd = cmd->next->next;
		else
			return (cmd->token);
	}
	return (NULL);
}

char	*get_path(t_env *env)
{
	if (!env)
		return (NULL);
	while (env && ft_strncmp(env->key, "PATH", 5))
		env = env->next;
	if (!env)
		return (NULL);
	return (env->value);
}

int	path_join(char *cmd, char *path, char **res)
{
	int		len;
	int		i;

	len = ft_strlen(path) + ft_strlen(cmd) + 1;
	if (ft_strlen(path) && path[ft_strlen(path) - 1] != '/')
		len++;
	*res = (char *)malloc(len);
	if (!*res)
		return (1);
	i = 0;
	while (*path)
		(*res)[i++] = *(path++);
	if (*(path - 1) != '/')//seg check
		(*res)[i++] = '/';
	while (*cmd)
	{
		(*res)[i++] = *(cmd++);
	}
	(*res)[i] = 0;
	return (0);
}

int	set_to_path(t_env *env, char *cmd, char **path)
{
	char	**paths;
	char	*tmp;
	int		i;

	tmp = NULL;
	if (!cmd)
		return (1);
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, F_OK) || access(cmd, X_OK))
			return (errno);
		*path = cmd;
		return (0);
	}
	if (get_path(env))
		paths = ft_split(get_path(env), ':');
	else
		return (127);
	if (!paths)
		return (1);
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

int print_err(char *s)
{
	char	*str;
	int		len;
	
	len = ft_strlen(s);
	str = (char *)malloc(32 + len);
	if (!str)
		return (1);
	ft_memcpy(str, "minishell: ", 11);
	ft_memcpy(str + 11, s, len);
	ft_memcpy(str + 11 + len, ": command not found\n", 20);
	str[31 + len] = 0;
	write(2, str, len + 31);
	free(str);
	return (0);
}

void	tkn_cleanup(t_tkn *tkn_list, char **cmd)
{
	if (!tkn_list)
		return ;
	if (cmd && tkn_list->token == *cmd)
	{
		tkn_list->token = NULL;
		cmd++;
	}
	tkn_cleanup(tkn_list->next, cmd);
	if (tkn_list->token)
		free(tkn_list->token);
	free(tkn_list);
}

void	cleanup(t_data *data, char **cmd)
{
	tkn_cleanup(data->tkn_list, cmd);
	if (data->env_list != NULL)
		ft_envclear(&(data->env_list));
	if (data->hrdc)
		free(data->hrdc);
	if (data)
		free(data);
}

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
		return(print_err(cmd->token), free_split(&envp), ret);
	}
	args = convertion(cmd, arg_len(cmd));
	if (!args)
		return (free(path), free_split(&envp), 1);
	cleanup(data, args);
	execve(path, args, envp);
	return (127);
}

int	is_builtin(t_data *data)
{
	char	*cmd;

	cmd = get_cmd(data->tkn_list);
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	red_in_out(t_tkn *cmd)
{
	int	redout;
	int	redin;
	
	redout = 0;
	redin = 0;
	while (cmd)
	{
		if (cmd->type == RED_OUT || cmd->type == APPND)
			redout = 1;
		if (cmd->type == RED_IN || cmd->type == HRDC)
			redin = 2;
		cmd = cmd->next;
	}
	return (redin + redout);
}

int	builtin_call(t_data *data, t_tkn *cmd)
{
	int	redtype;
	int	fd_in;
	int	fd_out;

	redtype = red_in_out(cmd);
	if (redtype == 1 || redtype == 3)
		fd_out = dup(STDOUT_FILENO);
	if (redtype == 2 || redtype == 3)
		fd_in = dup(STDIN_FILENO);
	if (redirection(data, cmd))
		return (1);
	data->args = convertion(cmd, arg_len(cmd));
	if (!data->args)
		return (1);
	data->exit_status = call(data);
	if ((redtype == 1 || redtype == 3) && dup2(fd_out, STDOUT_FILENO) < 0)
		return (close(fd_out), 1);
	if ((redtype == 2 || redtype == 3) && dup2(fd_in, STDIN_FILENO) < 0)
		return (close(fd_in), 1);
	if (redtype == 1 || redtype == 3)
		close(fd_out);
	if (redtype == 2 || redtype == 3)
		close(fd_in);
	return (0);
}

int	no_pipes(t_data *data, t_tkn *cmd)
{
	int		pid;
	int		ret;

	pid = fork();
	if (pid < 0)
		return (perror("minishell"), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ret = redirection(data, cmd);
		if (ret)
		{
			free_data(data);
			write(2, "Redirection error\n", 18);
			exit(ret);
		}
		ret = child_process(data, cmd);
		free_data(data);
		exit(ret);
	}
	waitpid(pid, &data->exit_status, 0);
	return (0);
}

int	execution(t_data *data, t_tkn *cmd)
{
	int	ret;

	ret = open_heredocs(data);
	setup_prompt_signals();
	if (ret)
		return (ret);
	if (!next_pipe(cmd))
	{
		if (is_builtin(data))
		{
			ret = builtin_call(data, cmd);
			return (ret);
		}
		else
			ret = no_pipes(data, cmd);
	}
	else
		ret = pipes(data, cmd);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	if (WIFSIGNALED(data->exit_status))
		data->exit_status = WTERMSIG(data->exit_status) + 128;
	return (data->exit_status);
}
