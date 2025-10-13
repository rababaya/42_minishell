/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:38:13 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/13 15:59:16 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_equal(char *args, t_env *export)
{
	t_env	*find;
	t_env	*new;
	char	*key;

	find = ft_envfind(export, args);
	if (find)
		return (1);
	key = ft_strdup(args);
	if (!key)
		return (ft_envclear(&export), 0);
	new = ft_envnew(key, NULL);
	if (!new)
		return (free(key), ft_envclear(&export), 0);
	ft_envadd_back(&export, new);
	return (1);
}

int	equal_only_helper(char *value, t_env *export, t_env *find, char *key)
{
	if (find->value)
		free(find->value);
	find->value = ft_strdup(value);
	if (!find->value)
		return (free(key), free(value), ft_envclear(&export), 0);
	return (free(key), free(value), 1);
}

int	equal_only(char	*args, t_env *export, char *equal)
{
	t_env	*find;
	char	*key;
	char	*value;

	key = ft_substr(args, 0, equal - args);
	if (!key)
		return (ft_envclear(&export), 0);
	value = ft_strdup(equal + 1);
	if (!value)
		return (free(key), ft_envclear(&export), 0);
	find = ft_envfind(export, key);
	if (!find)
	{
		find = ft_envnew(key, value);
		if (!find)
			return (free(key), free(value), ft_envclear(&export), 0);
		return (ft_envadd_back(&export, find), 1);
	}
	else
		return (equal_only_helper(value, export, find, key));
}

int	equal_plus_helper(char *tmp, t_env *export, t_env *find, char *key)
{
	char	*value;

	if (find->value)
	{
		value = ft_strjoin(find->value, tmp);
		if (!value)
			return (free(key), free(tmp), ft_envclear(&export), 0);
		free(find->value);
		find->value = value;
	}
	else
	{
		find->value = ft_strdup(tmp);
		if (!find->value)
			return (free(key), free(tmp), ft_envclear(&export), 0);
	}
	return (free(key), free(tmp), 1);
}

int	equal_plus(char	*args, t_env *export, char *plus)
{
	t_env	*find;
	char	*tmp;
	char	*key;

	key = ft_substr(args, 0, plus - args);
	if (!key)
		return (ft_envclear(&export), 0);
	tmp = ft_strdup(plus + 2);
	if (!tmp)
		return (free(key), ft_envclear(&export), 0);
	find = ft_envfind(export, key);
	if (!find)
	{
		find = ft_envnew(key, tmp);
		if (!find)
			return (free(key), free(tmp), ft_envclear(&export), 0);
		ft_envadd_back(&export, find);
		return (1);
	}
	else
		return (equal_plus_helper(tmp, export, find, key));
}
