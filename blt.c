/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:33 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/16 17:34:22 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*parse_env(char **env)
{
	int		j;
	char	*key;
	char	*value;
	t_env	*env_list;
	t_env	*tmp;

	env_list = NULL;
	while (*env)
	{
		j = 0;
		while ((*env)[j] != '=')
			j++;
		key = ft_substr(*env, 0, j);
		if (!key)
			return (ft_envclear(&env_list), NULL);
		value = ft_substr(*env, j + 1, ft_strlen(*env) - j - 1);
		if (!value)
			return (free(key), ft_envclear(&env_list), NULL);
		tmp = ft_envnew(key, value);
		if (!tmp)
			return (free(key), free(value), ft_envclear(&env_list), NULL);
		ft_envadd_back(&env_list, tmp);
		env++;
	}
	return (env_list);
}
