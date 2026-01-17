/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:22:40 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 18:23:42 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_builtin(t_tkn *tkn)
{
	char	*cmd;

	cmd = get_cmd(tkn);
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
