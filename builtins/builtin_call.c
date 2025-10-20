/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_call.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:35:58 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/20 14:06:43 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call(char **args, t_env *env_list)
{
	if (!ft_strncmp(args[0], "echo", 5))
	{
		if (ft_echo(args) < 0)
			return (-1);
	}
	else if (!ft_strncmp(args[0], "pwd", 4))
	{
		if (ft_pwd(env_list) < 0)
			return (-1);
	}
	else if (!ft_strncmp(args[0], "env", 4))
	{
		if (ft_env(args, env_list) < 0)
			return (-1);
	}
	else if (!ft_strncmp(args[0], "export", 4))
	{
		if (ft_export(args, env_list) < 0)
			return (-1);
	}
	else if (!ft_strncmp(args[0], "unset", 4))
	{
		if (ft_unset(args, env_list) < 0)
			return (-1);
	}
	return (1);
}
