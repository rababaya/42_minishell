/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:59:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/15 15:05:29 by dgrigor2         ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	env_list = parse_env(env);
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
		tkn = NULL;
		if (tokenise(&tkn, input))
		{
			printf ("tokenisation issue\n");
			ft_tknclear(&tkn);
			free(input);
			return (0);//errno
		}
		if (!tkn)//wrong quote punctuation should not exit minishell
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
					printf("expansion issue\n");
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
		ft_tknprint(tkn);
		// printf("fdsf\n");
		args = convertion(tkn);
		if (!args)
		{
			ft_tknclear(&tkn);
			free(input);
			printf("args issue\n");
			return (0);//errno
		}
		if (call(args, env_list) == -1)
			printf("lav ches ara");
		//ft_tknprint(tkn);
		// printf("fdsf\n");
		free(args);
		ft_tknclear(&tkn);
		free(input);
	}
	ft_envclear(&env_list);
}
