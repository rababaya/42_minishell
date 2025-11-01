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

void	free_mat(char **s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		++i;
	}
}

int	main(int argc, char **argv, char **env)
{
	//	t_env	*env_list;
	char	*input;
	//char **args = &argv[1];
	t_tkn	*tkn;
	t_tkn	*tmp;
	char	**mat;
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
		{
			printf ("readline error\n");
			break ;
		}
		if (!*input)
			continue ;
		if (!ft_strncmp(input, "exit", 5))
			break ;
		add_history(input);
		tkn = tokenise(input);//224666
		if (!tkn)//Dzyadz, ba vor tokend datark exav inch es anelu, hn? xosqi goyutuyun chunecox popoxakan
		{
			printf ("tokenisation issue\n");
			ft_envclear(&a);
			ft_tknclear(&tkn);
			free(input);
			return (0);//errno
		}
		tmp = tkn;
		while (tmp)
		{
			if (tmp->type == 1)
			{
				status = expand(tmp, a, a);
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
		argv = convertion(tkn);
		mat = argv;
		if (!argv)
		{
			ft_tknclear(&tkn);
			free(input);
			return (0);//errno
		}
		while (*argv)
		{
			printf("token:   %s\n", *argv);
			argv++;
		}
		//ft_tknprint(tkn);
		free(mat);
		ft_tknclear(&tkn);
		free(input);

	}
}
