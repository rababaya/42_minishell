/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/12/03 16:09:02 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
some error codes
cmd not found 127
is a file/isa directory 126
no such file 1

*/
int g_exit_status = 0;

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	char	*input;
	t_tkn	*tkn;
	t_tkn	*tmp;
	int		status;
	char	**args;
	t_data	*data;
	
	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	env_list = parse_env(env);
	data = data_init();
	data->env_list = env_list;                               ////////////////////
	status = 0;
	printf("%d\n", access("Makefil", R_OK));
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("<minishell>");
		if (!input)
		{
			print("exit\n");
			free_data(data);
			exit(0);
		}
		if (!*input)
			continue ;
		add_history(input);
		tkn = NULL;
		if (!check_punctuation(input))
		{
			printf("wrong quote punctuation\n");
			continue ;
		}
		if (tokenise(&tkn, input))
		{
			ft_putstr_fd("tokenisation issue\n", 2);
			free_data(data);
			free(input);//shouldn't data be cleared?
			return (127);
		}
		if (!tkn)
		{
			free(input);
			continue ;
		}
		tmp = tkn;
		while (tmp)
		{
			if (tmp->type == ARG)
			{
				
				status = expand(tmp, env_list);
				if (status)
				{
					free_data(data);
					free(input);//data clear?
					ft_putstr_fd("expansion issue\n", 2);
					return (127);//errno
				}
			}
			tmp = tmp->next;
		}
		remove_empties(&tkn);
		if (!tkn)
		{
			free(input);
			continue;
		}
		data->tkn_list = tkn;                                  ////////////////
		args = convertion(tkn);
		if (!args)
		{
			free_data(data);
			free(input);
			ft_putstr_fd("args issue\n", 2);
			return (127);//errno
		}
		data->args = args;                                 /////////////////////
		// ft_tknprint(data->tkn_list);
		g_exit_status = call(data);
		if (g_exit_status == 1)
			execution(data, tkn->token);
		free(args);
		data->args = NULL;
		ft_tknclear(&tkn);
		data->tkn_list = NULL;
		free(input);
	}
}
