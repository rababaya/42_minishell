/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/05 20:06:27 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
some error codes
cmd not found 127
is a file/isa directory 126
no such file 1
*/
int g_sig_status = 0;

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_tkn	*tmp;
	int		status;
	t_data	*data;
	
	(void)argc;
	(void)argv;
	data = data_init();
	if (!data)
		return (0);
	data->env_list = parse_env(env);
	if (!data->env_list)
		return(free_data(data), 1);
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
		add_history(input);
		if (!check_punctuation(input))
			continue ;
		if (tokenise(&(data->tkn_list), input))
			return (free_data(data), free(input), 1);
		free(input);
		if (!data->tkn_list)
			continue ;
		tmp = data->tkn_list;
		while (tmp)
		{
			if (tmp->type == HRDC)
			{
				heredoc(data, tmp);
				tmp = tmp->next;
			}
			else if (tmp->type == ARG)
			{
				status = expand(tmp, data->env_list);
				if (status)
					return (free_data(data), 127);
			}
			tmp = tmp->next;
		}
		remove_empties(&(data->tkn_list));
		if (!data->tkn_list)
			continue;
		// ft_tknprint(data->tkn_list);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		execution(data, data->tkn_list);
		if (data->exit_status == 130)
			write(1, "\n", 1);
		if (data->exit_status == 131)
			print("Quit (core dumped)\n");
		free(data->args);
		data->args = NULL;
		ft_tknclear(&data->tkn_list);
	}
	return (0);
}
