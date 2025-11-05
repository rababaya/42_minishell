/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/05 15:43:50 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **env)
// {
// 	t_env	*env_list;
// 	char	**args;
// 	char	*input;

// 	(void)argc;
// 	(void)argv;
// 	env_list = parse_env(env);
// 	//export = lst_to_str(env_list);
// 	// ft_envprint(env_list);
// 	// call(&argv[1], env_list);
// 	// lst_to_str(env_list);
// 	// ft_envclear(&env_list);
// 	while (1)
// 	{
// 		input = readline("<minishell>");
// 		if (!input)
// 			break ;
// 		args = ft_split(input, ' ');
// 		if (call(args, env_list) == -1)
// 			printf("lav ches ara");
// 		add_history(input);
// 		free_split(&args);
// 		free(input);
// 	}
// 	free_split(&args);
// 	ft_envclear(&env_list);
// }







int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	char	*input;
	t_tkn	*tkn;
	t_tkn	*tmp;
	int		status;

	char	**args;

	
	(void)argc;
	(void)argv;
	//ft_echo(args);
	// (void)env;
	env_list = parse_env(env);
	// ft_envprint(env_list);
	// lst_to_str(env_list);
	// ft_envclear(&env_list);
	tkn = NULL;

	(void)tkn;
	status = 0;
	while (1)
	{
		input = readline("<minishell>");
		if (!input)
		{
			printf ("readline error\n");
			break ;
		}
		if (!*input)
			continue ;
		add_history(input);
		tkn = tokenise(input);//224666
		if (!tkn)//Dzyadz, ba vor tokend datark exav inch es anelu, hn? xosqi goyutuyun chunecox popoxakan
		{
			printf ("tokenisation issue\n");
			ft_tknclear(&tkn);
			free(input);
			return (0);//errno
		}
		tmp = tkn;
		while (tmp)
		{
			if (tmp->type == 1)
			{
				status = expand(tmp, env_list, env_list);
				if (status)
				{
					ft_tknclear(&tkn);
					free(input);
					write(1, "nigga\n", 6);
					return (status);//replace with actual errno maybe?
				}
			}
			tmp = tmp->next;
		}
		args = convertion(tkn);
		if (!args)
		{
			ft_tknclear(&tkn);
			free(input);
			return (0);//errno
		}
		if (call(args, env_list) == -1)
			printf("lav ches ara");
		//ft_tknprint(tkn);
		free(args);
		ft_tknclear(&tkn);
		free(input);
	}
	ft_envclear(&env_list);
}

