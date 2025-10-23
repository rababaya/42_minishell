/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/23 15:42:38 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	//	t_env	*env_list;
	char	*input;
	//char **args = &argv[1];
	t_tkn	*tkn;
	t_tkn	*tmp;
	int		status;
	
	(void)argc;
	(void)argv;
	//ft_echo(args);
	(void)env;
	// env_list = parse_env(env);
	// ft_envprint(env_list);
	// lst_to_str(env_list);
	// ft_envclear(&env_list);
	tkn = NULL;
	t_env	*a;

	a = ft_envnew(ft_strdup("popox"), ft_strdup("akan"));
	(void)a;
	(void)tkn;
	status = 0;
	while (1)
	{
		input = readline("<minishell>");
		if (!input)
			break ;
		if (!ft_strncmp(input, "exit", 5))
			break ;
		add_history(input);
		tkn = tokenise(input);//224666
		tmp = tkn;
		// ft_tknprint(tkn);
		while (tmp)
		{
			if (tmp->type == 1)
			{
				status = expand(tmp, a, a);
				if (status)
				{
					ft_tknclear(&tkn);
					free(input);
					return (status);//replace with actual errno maybe?
				}
			}
			tmp = tmp->next;
		}
		ft_tknprint(tkn);
		ft_tknclear(&tkn);
		free(input);
		
	}
	ft_envdelone(a);
}
