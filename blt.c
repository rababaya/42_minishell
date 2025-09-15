/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:33 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/15 19:10:11 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char **s, size_t count)
{
	size_t	i;

	i = 0;
	if (count == 0)
	{
		while ((s)[i])
		{
			free((s)[i]);
			i++;
		}
	}
	else
	{	
		while (i < count)
		{
			free((s)[i]);
			++i;
		}
	}
	free(s);
	s = NULL;
	return ;
}

t_env	*parse_env(char **env)
{
    int     i;
    char    **key_value;
    t_env   *env_list;
    t_env   *tmp;
    
    i = 0;
	key_value = ft_split(env[i], '=');
	env_list = ft_envnew(key_value[0], key_value[1]);
	i++;
	free_split(key_value, 0);
    while (env[i])
    {
        key_value = ft_split(env[i], '=');
		if (!key_value)
			return (ft_envclear(&env_list), NULL);
    	tmp = ft_envnew(key_value[0], key_value[1]);
		if (!tmp)
			return (free_split(key_value, 0), ft_envclear(&env_list), NULL);
	    ft_envadd_back(&env_list, tmp);
		free_split(key_value, 0);
		i++;
    }
    return (env_list);
}
