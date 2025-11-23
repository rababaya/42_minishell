/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:58:44 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/13 14:28:09 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envprint(t_env *env_list)
{
	while (env_list)
	{
		if (env_list->value != NULL)
		{
			if (print(env_list->key) < 0)
				return (-1);
			if (print("=") < 0)
				return (-1);
			if (print(env_list->value) < 0)
				return (-1);
			if (print("\n") < 0)
				return (-1);
		}
		env_list = env_list->next;
	}
	return (1);
}

int	ft_exportprint(t_env *export)
{
	while (export)
	{
		if (!ft_strncmp(export->key, "_", 2))
		{
			export = export->next;
			continue ;
		}
		if (print("declare -x ") < 0)
			return (-1);
		if (print(export->key) < 0)
			return (-1);
		if (export->value != NULL)
		{
			if (print("=\"") < 0)
				return (-1);
			if (print(export->value) < 0)
				return (-1);
			if (print("\"") < 0)
				return (-1);
		}
		if (print("\n") < 0)
			return (-1);
		export = export->next;
	}
	return (1);
}
