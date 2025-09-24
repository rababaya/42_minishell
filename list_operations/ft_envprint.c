/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:58:44 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/24 16:17:44 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envprint(t_env *env_list)
{
	while (env_list)
	{
		if (print(env_list->key) < 0)
			return (-1);
		if (print("=") < 0)
			return (-1);
		if (env_list->value)
		{
			if (print(env_list->value) < 0)
				return (-1);
		}
		if (print("\n") < 0)
			return (-1);
		env_list = env_list->next;
	}
	return (1);
}
