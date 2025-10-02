/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:19:19 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/03 00:29:31 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_node_swap(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->key;
	a->key = b->key;
	b->key = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

void	ft_sort_list(t_env *export)
{
	t_env	*i;
	t_env	*j;

	if (!export)
		return ;
	i = export;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strncmp(i->key, j->key, ft_strlen(i->key)) > 0)
				ft_node_swap(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

int	ft_export(char **args, t_env *export)
{
	int		j;
	char	*key;
	char	*value;
	t_env	*tmp;
	char	*equal;

	j = 0;
	if (!args[1])
		return (ft_sort_list(export), ft_exportprint(export), 0);
	while (*(++args))
	{
		if (!ft_isalpha((*args)[0]) && (*args)[0] != '_')
			if (printf("minishell: export: `%s': not a valid identifier",
					*args) < 0)
				return (perror("minishell"), 1);
		equal = ft_strchr(*args, '=');
		if (!equal)
		{
			key = ft_strdup(*args);
			if (!key)
				return (ft_envclear(&export), 1);
			value = NULL;
		}
		else if (equal && equal + 1 == '+')
		{
			j = equal - *args;
			key = ft_substr(*args, 0, j);
			if (!key)
				return (ft_envclear(&export), 1);
			tmp = ft_envfind(export, key);
			if (tmp)
			{
				value = ft_substr(*args, j + 1, ft_strlen(*args) - j - 1);
				if (!value)
					return (free(key), ft_envclear(&export), 1);
				tmp->value = ft_strjoin(tmp->value, value);
			}
		}
		else
		{
			j = equal - *args;
			key = ft_substr(*args, 0, j);
			if (!key)
				return (ft_envclear(&export), 1);
			value = ft_substr(*args, j + 1, ft_strlen(*args) - j - 1);
			if (!value)
				return (free(key), ft_envclear(&export), 1);
		}
		tmp = ft_envnew(key, value);
		if (!tmp)
			return (free(key), free(value), ft_envclear(&export), 1);
		ft_envadd_back(&export, tmp);
	}
	ft_exportprint(export);
	printf("////////////////////////////////////////////////////");
	ft_envprint(export);
	return (1);
}
