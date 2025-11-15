/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:43:03 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/15 18:11:57 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data)
{
	if (data->args[1])
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(data->args[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		return (127);
	}
	if (ft_envprint(data->env_list) < 0)
		return (-1);
	return (1);
}
