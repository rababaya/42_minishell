/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:37:51 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/29 14:06:04 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data)
{
	int	i;

	i = -1;
	if (!(data->args[1]))
		return (0);
	while (data->args[++i])
		ft_envdelone(&(data->env_list), data->args[i]);
	return (0);
}
