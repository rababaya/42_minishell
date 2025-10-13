/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:04:23 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/13 14:46:04 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envfind(t_env *env_list, char *key)
{
	while (env_list && ft_strncmp(env_list->key, key, ft_strlen(key)))
		env_list = env_list->next;
	return (env_list);
}
