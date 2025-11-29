/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:35:58 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/15 16:13:15 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call(t_data *data)
{
	if (!ft_strncmp(data->args[0], "echo", 5))
		return (ft_echo(data));
	else if (!ft_strncmp(data->args[0], "pwd", 4))
		return (ft_pwd(data));
	else if (!ft_strncmp(data->args[0], "env", 4))
		return (ft_env(data));
	else if (!ft_strncmp(data->args[0], "export", 7))
		return (ft_export(data));
	else if (!ft_strncmp(data->args[0], "unset", 6))
		return (ft_unset(data));
	else if (!ft_strncmp(data->args[0], "cd", 3))
		return (ft_cd(data));
	else if (!ft_strncmp(data->args[0], "exit", 5))
		return (ft_exit(data));
	return (1);
}
