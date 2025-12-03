/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:23:20 by rababaya          #+#    #+#             */
/*   Updated: 2025/12/03 16:51:38 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->args = NULL;
	data->env_list = NULL;
	data->tkn_list = NULL;
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
	if (data)
		free(data);
}
