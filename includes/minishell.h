/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:00:16 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 18:08:48 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"
# include "list_ops.h"
# include "builtins.h"
# include "tokenisation.h"
# include "utils.h"
# include "execution.h"

extern int	g_sig_status;

typedef struct s_data
{
	t_env	*env_list;
	t_tkn	*tkn_list;
	char	**args;
	int		exit_status;
	t_hrdc	*hrdc;
}	t_data;

t_env	*parse_env(char **env);
char	**lst_to_str(t_env *env);

void	heredoc_sigint(int sig);
void	setup_heredoc_signals(void);
void	setup_main_signals(void);
void	setup_prompt_signals(void);
void	sigint_handler(int sig);
int		start_expansion(t_data *data);
int		check_input(char *input);

int		process_input(t_data *data, char *input);

#endif