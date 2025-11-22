/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:19:19 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/20 13:13:08 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_node_swap(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->key;
	a->key = b->key;
	b->key = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

static void	ft_sort_list(t_env *export)
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

static void	export_helper(char **args, t_env *export, int *ret)
{
	char	*equal;

	if (!ft_isalpha((*args)[0]) && (*args)[0] != '_')
	{
		*ret = 1;
		printf("minishell: export: `%s': not a valid identifier\n", *args);
	}
	equal = ft_strchr(*args, '=');
	if (!equal)
	{
		if (!no_equal(*args, export))
			*ret = 2;
	}
	else if (equal && *(equal - 1) != '+')
	{
		if (!equal_only(*args, export, equal))
			*ret = 2;
	}
	else
		if (!equal_plus(*args, export, equal - 1))
			*ret = 2;
}

int	ft_export(char **args, t_env *export)
{
	int	ret;

	ret = 0;
	if (!args[1])
		return (ft_sort_list(export), ft_exportprint(export), ret);
	while (*(++args))
		export_helper(args, export, &ret);
	return (ret);
}
