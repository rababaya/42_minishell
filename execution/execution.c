/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:01:00 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/12/03 16:44:17 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (127);
	i = 0;
	while (*path)
		(*res)[i++] = *(path++);
	if (*(path - 1) != '/')//seg check
		(*res)[i++] = '/';
	while (*cmd)
	{
		(*res)[i++] = *(cmd++);
	}
	return (0);	
}

int	set_to_path(t_env *env, char *cmd, char **path)
{
	char	**paths;
	char	*tmp;
	
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, F_OK))
			return (127);//errno of no such file
		if (access(cmd, X_OK))
			return (126);//errno of permission denied
		*path = cmd;
		return (0);
	}
	if (get_path(env))
		paths = ft_split(get_path(env), ':');
	else
	 	return (127);//
	if (!paths)
		return (127);
	while (*paths)
	{
		if (path_join(cmd, *paths, &tmp))
			return (127);
		if (!access(tmp, F_OK) && !access(tmp, X_OK))
		{
			*path = tmp;
			return (0);
		}
		free(tmp);
		paths++;
	}
	return (127);
}

int	execution(t_data *data, char *cmd)
{
	int	pid;
	char	*path;
	char	**argv;
	char	**envp;

	pid = fork();
	if (pid < 0)
		return (127);
	if (pid == 0)
	{
		argv = convertion(data->tkn_list);
		if (!argv)
			return (127);
		envp = lst_to_str(data->env_list);
		if (!envp)
			return (free_split(&argv), 127);
		if (set_to_path(data->env_list,
			 cmd,
			  &path))
			return (free_split(&envp), free_split(&argv), 127);
		execve(path, argv, envp);
		return (127);
	}
	wait(NULL);
	return (0);
}