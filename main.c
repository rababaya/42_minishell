/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/02 17:27:50 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	//char	**export;
	// char	*input;
	
	(void)argc;
	// (void)env;
	env_list = parse_env(env);
	//export = lst_to_str(env_list);
	// ft_envprint(env_list);
	call(&argv[1], env_list);
	// lst_to_str(env_list);
	// ft_envclear(&env_list);
	// while (1)
	// {
	// 	input = readline("<minishell>");
	// 	if (!input)
	// 		break ;
	// 	add_history(input);
	// 	free(input);
	// }
}
