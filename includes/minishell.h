/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:00:16 by rababaya          #+#    #+#             */
/*   Updated: 2025/12/13 10:26:41 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include "list_ops.h"
# include "builtins.h"
# include "utils.h"
# include "tokenisation.h"
# include "ast.h"
# include "execution.h"

extern int	g_exit_status;

typedef struct s_data
{
	t_env	*env_list;
	t_tkn	*tkn_list;
	char	**args;
}	t_data;

t_env	*parse_env(char **env);
char	**lst_to_str(t_env *env);

void	sigint_handler(int sig);

#endif