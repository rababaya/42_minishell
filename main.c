/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 18:06:39 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig_status = 0;

int	start_expansion(t_data *data)
{
	t_tkn	*tmp;
	int		status;

	tmp = data->tkn_list;
	while (tmp)
	{
		if (tmp->type == ARG)
		{
			status = expand(tmp, data);
			if (status)
			{
				return (free_data(data), 1);
			}
		}
		if (tmp->type == HRDC && tmp->next)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (0);
}

void	check_exit_status(t_data *data)
{
	if (g_sig_status != 0)
	{
		data->exit_status = g_sig_status;
		g_sig_status = 0;
	}
}

int	check_input(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	if (!input || !*input)
		return (0);
	while (input[++i])
	{
		if (input[i] == ' ')
			count++;
	}
	if (count == i)
		return (0);
	return (1);
}

t_data	*init_minishell(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = data_init();
	if (!data)
		return (NULL);
	data->env_list = parse_env(env);
	if (!data->env_list)
	{
		free_data(data);
		return (NULL);
	}
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;
	int		status;

	data = init_minishell(argc, argv, env);
	if (!data)
		return (1);
	while (1)
	{
		setup_main_signals();
		input = readline("<minishell> ");
		check_exit_status(data);
		if (!input)
		{
			print("exit\n");
			status = data->exit_status;
			free_data(data);
			break ;
		}
		status = process_input(data, input);
		if (status)
			return (status);
	}
	rl_clear_history();
	return (status);
}
