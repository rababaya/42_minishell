/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:58:44 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/16 17:17:48 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envprint(t_env *env_list)
{
	while (env_list)
	{
		printf("%s=", env_list->key);
		if (env_list->value)
			printf("%s\n", env_list->value);
		else
			printf("\n");
		env_list = env_list->next;
	}
}
