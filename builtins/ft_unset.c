/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:37:51 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/15 16:01:28 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data)
{
	int	ret;

	ret = 0;
	if (!(data->args[1]))
		return (ret);
	while (*(++(data->args)))
		ft_envdelone(&(data->env_list), *(data->args));
	return (0);
}
