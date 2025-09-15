/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/15 18:53:11 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	// char	*input;
	t_env	*tmp;
	t_env	*env_list;
	
	(void)argc;
	(void)argv;
	env_list = parse_env(env);

	tmp = env_list;
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	
	ft_envclear(&tmp);
	// while (1)
	// {
	// 	input = readline("<minishell>");
	// 	if(!input)
	// 		break ;
	// 	add_history(input);
	// 	free(input);
	// }
}
