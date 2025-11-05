/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:37:51 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/05 15:56:42 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, t_env *export)
{
	int	ret;

	ret = 0;
	if (!args[1])
		return (ret);
	while (*(++args))
		ft_envdelone(&export, *args);
	return (0);
}
