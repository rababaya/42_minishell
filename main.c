/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/15 18:46:08 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_empties(t_tkn **tkn)
{
	t_tkn	*tmp;
	t_tkn	*scnd;

	tmp = *tkn;
	while (tmp && !(tmp->token))
	{
		*tkn = tmp->next;
		free(tmp);
		tmp = *tkn;
	}
	while (tmp && tmp->next)
	{
		if (!(tmp->next->token))
		{
			scnd = tmp->next->next;
			free(tmp->next);
			tmp->next = scnd;
		}
		else
		{
			tmp = tmp->next;
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	char	*input;
	t_tkn	*tkn;
	t_tkn	*tmp;
	int		status;
	char	**args;
	t_data	*data;

	(void)argc;
	(void)argv;
	env_list = parse_env(env);
	data = data_init();
	data->env_list = env_list;                               ////////////////////
	status = 0;
	while (1)
	{
		input = readline("<minishell>");
		if (!input)
		{
			free_data(data);
			break ;
		}
		if (!*input)
			continue ;
		add_history(input);
		tkn = NULL;
		if (tokenise(&tkn, input))
		{
			ft_putstr_fd("tokenisation issue\n", 2);
			ft_tknclear(&tkn);
			free(input);
			return (0);//errno
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
				
				status = expand(tmp, env_list, env_list);
				if (status)
				{
					ft_tknclear(&tkn);
					free(input);
					ft_putstr_fd("expansion issue\n", 2);
					return (status);//replace with actual errno maybe?
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
			return (0);//errno
		}
		data->args = args;                                 /////////////////////
		ft_tknprint(data->tkn_list);
		if (call(data) == -1)
			ft_putstr_fd("lav ches ara", 2);
		free(args);
		data->args = NULL;
		ft_tknclear(&tkn);
		data->tkn_list = NULL;
		free(input);
	}
}
