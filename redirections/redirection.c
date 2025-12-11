/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:25:02 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/12/11 16:32:15 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection(t_data *data, t_tkn *cmd)
{
	// while (cmd && cmd->type != REDIR)
	// 	cmd = cmd->next;
	// if ()
}


/*
int	execution(t_data *data, t_tkn *cmd, char *dst)
{
	int		pid;
	int		ret;
	int		fd;
	char	*path;
	char	**argv;
	char	**envp;

	pid = fork();
	if (pid < 0)
		return (127);
	if (pid == 0)
	{
		if (dst)
		{
			if (access(dst, F_OK))
				return (127);//errno of no such file
			if (access(dst, W_OK))
				return (126);
			fd = open(dst, O_WRONLY);
			if (fd < 0)
				return (1); //I have no idea what error is this
			dup2(1, fd);
		}
		path = NULL;
		argv = convertion(data->tkn_list);//or cmd??
		if (!argv)
			return (127);
		envp = lst_to_str(data->env_list);
		if (!envp)
			return (free(argv), 127);
		if (set_to_path(data->env_list, cmd->token, &path))
		{
			free(argv);
			free_split(&envp);
			if (path)
				free(path);
			free_data(data);///leave only if exiting from here istead of returning to main function
			exit (127);
		}
		execve(path, argv, envp);
		return (127);
	}
	waitpid(pid, &ret, 0);
	return (ret);
}

*/