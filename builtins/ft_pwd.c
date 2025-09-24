/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:33:58 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/24 16:13:07 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *env_list)
{
	char	*pwd;
	
	env_list = ft_envfind(env_list, "PWD");
	if (env_list)
	{
		if (print(env_list->value) < 0)
			return (-1);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (print(pwd) < 0)
			return (free(pwd), -1);
		free(pwd);
	}
	if (print("\n") < 0)
		return (-1);
	return (1);
}
