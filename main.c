/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 16:02:19 by rababaya         ###   ########.fr       */
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

t_data	*init_minishell(char **env)
{
	t_data	*data;

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

int	handle_input_validation(char *input)
{
	if (!check_input(input))
	{
		free(input);
		return (0);
	}
	add_history(input);
	if (!check_punctuation(input))
	{
		free(input);
		return (0);
	}
	return (1);
}

int	process_tokenization(t_data *data, char *input)
{
	if (tokenise(&(data->tkn_list), input))
	{
		free_data(data);
		free(input);
		return (1);
	}
	free(input);
	if (start_expansion(data))
	{
		free_data(data);
		return (1);
	}
	if (syntax_check(data->tkn_list))
	{
		data->exit_status = 2;
		ft_tknclear(&(data->tkn_list));
		return (0);
	}
	return (2);
}

void	handle_execution_status(t_data *data)
{
	if (data->exit_status == 130)
		write(1, "\n", 1);
	if (data->exit_status == 131)
		print("Quit (core dumped)\n");
}

void	cleanup_after_execution(t_data *data)
{
	free(data->args);
	data->args = NULL;
	free_heredocs(data);
	ft_tknclear(&data->tkn_list);
	data->tkn_list = NULL;
}

int	process_input(t_data *data, char *input)
{
	int	status;

	if (!handle_input_validation(input))
		return (0);
	status = process_tokenization(data, input);
	if (status != 2)
		return (status);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (execution(data, data->tkn_list))
	{
		free_data(data);
		return (1);
	}
	handle_execution_status(data);
	cleanup_after_execution(data);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;
	int		status;

	(void)argc;
	(void)argv;
	data = init_minishell(env);
	if (!data)
		return (1);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
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
