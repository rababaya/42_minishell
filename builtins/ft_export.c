/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:19:19 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/29 13:58:40 by rababaya         ###   ########.fr       */
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

int	export_helper_helper(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[0]) && args[0] != '_')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	while (args[++i])
	{
		if ((args[i] == '+' && args[i + 1] == '=') || args[i] == '=')
			break ;
		if (!ft_isalnum(args[i]) && args[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}

static void	export_helper(char **args, t_env *export, int *ret)
{
	char	*equal;

	if (export_helper_helper(*args))
	{
		*ret = 1;
		return ;
	}
	equal = ft_strchr(*args, '=');
	if (!equal)
	{
		if (!no_equal(*args, export))
			*ret = 1;
	}
	else if (equal && *(equal - 1) != '+')
	{
		if (!equal_only(*args, export, equal))
			*ret = 1;
	}
	else
		if (!equal_plus(*args, export, equal - 1))
			*ret = 1;
}

int	ft_export(t_data *data)
{
	int	ret;

	ret = 0;
	if (!(data->args[1]))
		return (ft_sort_list(data->env_list),
			ft_exportprint(data->env_list), ret);
	while (*(++(data->args)))
		export_helper(data->args, data->env_list, &ret);
	return (ret);
}
