/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enviter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:56:40 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/15 17:07:09 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_enviter(t_env *env, void (*f)(void *))
{
	while (env && f)
	{
		f(env->key);
		f(env->value);
		env = env->next;
	}
	return ;
}
