/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:33:58 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/29 14:08:16 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	*pwd;
	t_env	*tmp;

	tmp = ft_envfind(data->env_list, "PWD");
	if (tmp)
	{
		if (print(tmp->value) < 0)
			return (1);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			perror("pwd");
			return (1);
		}
		if (print(pwd) < 0)
			return (free(pwd), 1);
		free(pwd);
	}
	if (print("\n") < 0)
		return (1);
	return (1);
}
