/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:44:33 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/02 16:21:04 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char ***s, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free((*s)[i]);
		++i;
	}
	free(*s);
	*s = NULL;
	return ;
}

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

char	**lst_to_str(t_env *env)
{
	int		size;
	int		i;
	char	*key_str;
	char	**env_str;

	size = ft_envsize(env);
	env_str = (char **)malloc((size + 1) * sizeof(char *));
	if (!env_str)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		key_str = ft_strjoin(env->key, "=");
		if (!key_str)
			return (free_split(&env_str, i), NULL);
		env_str[i] = ft_strjoin(key_str, env->value);
		if (!env_str)
			return (free_split(&env_str, i), free(key_str), NULL);
		free(key_str);
		env = env->next;
	}
	env_str[i] = NULL;
	return (env_str);
}
