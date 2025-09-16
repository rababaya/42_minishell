/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/16 17:38:00 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	// char	*input;
	
	(void)argc;
	(void)argv;
	env_list = parse_env(env);
	ft_envprint(env_list);
	ft_envclear(&env_list);
	// while (1)
	// {
	// 	input = readline("<minishell>");
	// 	if(!input)
	// 		break ;
	// 	add_history(input);
	// 	free(input);
	// }
}
