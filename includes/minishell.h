/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:00:16 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/10 18:43:48 by dgrigor2         ###   ########.fr       */
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
# include "ft_printf.h"
# include "list_ops.h"
# include "builtins.h"
# include "utils.h"
# include "tokenisation.h"
# include "execution.h"

extern int	g_sig_status;

typedef struct s_data
{
	t_env	*env_list;
	t_tkn	*tkn_list;
	char	**args;
	int		exit_status;
	int		in_fd;
	int		out_fd;
}	t_data;

t_env	*parse_env(char **env);
char	**lst_to_str(t_env *env);

void	sigint_handler(int sig);
void	heredoc_sigint(int sig);

#endif