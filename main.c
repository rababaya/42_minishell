/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/13 14:41:29 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	char	**args;
	char	*input;
	
	(void)argc;
	(void)argv;
	// (void)env;
	env_list = parse_env(env);
	//export = lst_to_str(env_list);
	// ft_envprint(env_list);
	// call(&argv[1], env_list);
	// lst_to_str(env_list);
	// ft_envclear(&env_list);
	while (1)
	{
		input = readline("<minishell>");
		if (!input)
			break ;
		args = ft_split(input, ' '); 
		call(args, env_list);
		add_history(input);
		free_split(&args);
		free(input);
	}
	free_split(&args);
	ft_envclear(&env_list);
}
