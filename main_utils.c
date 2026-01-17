/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:06:48 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 19:10:46 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_validation(char *input, t_data *data)
{
	if (!check_input(input))
	{
		data->exit_status = 2;
		free(input);
		return (0);
	}
	add_history(input);
	if (!check_punctuation(input))
	{
		data->exit_status = 2;
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
		ft_putstr_fd("Syntax error\n", 2);
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

	if (!handle_input_validation(input, data))
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
