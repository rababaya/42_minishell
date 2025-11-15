/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:43:03 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/15 16:03:39 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data)
{
	if (data->args[1])
		return (printf("env: ‘%s’: No such file or directory",
				data->args[1]), 127);
	if (ft_envprint(data->env_list) < 0)
		return (-1);
	return (1);
}
