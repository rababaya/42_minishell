/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:23:20 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/15 14:00:45 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->args = NULL;
	data->env_list = NULL;
	data->tkn_list = NULL;
	data->exit_status = 0;
	data->hrdc = NULL;
	return (data);
}

void	free_data(t_data *data)
{
	if (data->args != NULL)
		free(data->args);
	if (data->env_list != NULL)
		ft_envclear(&(data->env_list));
	if (data->tkn_list != NULL)
		ft_tknclear(&(data->tkn_list));
	if (data->hrdc)
		free(data->hrdc);
	data->hrdc = NULL;
	if (data)
		free(data);
}

void	clear_data(t_data *data)
{
	if (data->args != NULL)
		free(data->args);
	data->args = NULL;
	if (data->tkn_list != NULL)
		ft_tknclear(&(data->tkn_list));
	data->tkn_list = NULL;
}
