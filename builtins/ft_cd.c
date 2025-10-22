/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:46:44 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/22 17:30:11 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_helper(char *dir, t_env *env)
{
	t_env	*tmp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("minishell: cd"), 1);
	tmp = ft_envfind(env, "OLDPWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = pwd;
	}
	if (chdir(dir) == -1)
		return (perror("minishell: cd"), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("minishell: cd"), 1);
	tmp = ft_envfind(env, "PWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = pwd;
		return (0);
	}
	return (free(pwd), 0);
}

int	ft_cd(char **args, t_env *env)
{
	t_env	*tmp;

	if (!args[1])
	{
		tmp = ft_envfind(env, "HOME");
		if (!tmp)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		if (cd_helper(tmp->value, env))
			return (1);
	}
	else if (!args[2])
	{
		if (cd_helper(args[1], env))
			return (1);
	}
	else
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	return (0);
}
