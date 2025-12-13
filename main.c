/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/12/13 11:45:42 by dgrigor2         ###   ########.fr       */
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
	char	*input;
	t_tkn	*tmp;
	int		status;
	t_data	*data;
	
	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	data = data_init();
	if (!data)
		return (0);
	data->env_list = parse_env(env);//malloc protection??
	status = 0;
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
		if (!check_punctuation(input))
		{
			printf("wrong quote punctuation\n");
			continue ;
		}
		if (tokenise(&(data->tkn_list), input))
		{
			ft_putstr_fd("tokenisation issue\n", 2);
			free_data(data);
			free(input);
			return (127);
		}
		ft_tknprint(data->tkn_list);
		free(input);
		if (!data->tkn_list)
			continue ;
		tmp = data->tkn_list;
		while (tmp)
		{
			if (tmp->type == ARG)
			{
				status = expand(tmp, data->env_list);
				if (status)
				{
					free_data(data);
					ft_putstr_fd("expansion issue\n", 2);
					return (127);//errno
				}
			}
			tmp = tmp->next;
		}
		remove_empties(&(data->tkn_list));
		if (!data->tkn_list)
			continue;                                ////////////////
		data->args = convertion(data->tkn_list, -1);
		if (!data->args)
		{
			ft_putstr_fd("args issue\n", 2);
			free_data(data);
			return (127);//errno
		}                               /////////////////////
		// ft_tknprint(data->tkn_list);
		g_exit_status = call(data);
		if (g_exit_status == 1)
			g_exit_status = execution(data, data->tkn_list);
		free(data->args);
		data->args = NULL;
		ft_tknclear(&data->tkn_list);
	}
	return (0);
}
