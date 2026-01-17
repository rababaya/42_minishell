/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:21:52 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/17 18:24:42 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_hrdc
{
	t_tkn	*tkn;
	int		fd;
}			t_hrdc;

typedef struct s_pipes
{
	int		fd[2];
	int		*pid;
	int		len;
	int		lastread;
	int		i;
}			t_pipes;

int			execution(t_data *data, t_tkn *cmd);
int			child_process(t_data *data, t_tkn *cmd);
int			no_pipes(t_data *data, t_tkn *cmd);
int			set_to_path(t_env *env, char *cmd, char **path);
int			redirection(t_data *data, t_tkn *cmd);
t_tkn		*next_pipe(t_tkn *tkn);
int			pipe_count(t_tkn *tkn);
int			next_pipe_count(t_tkn *tkn);
int			pipes(t_data *data, t_tkn *tkn);
int			arg_len(t_tkn *tkn);
int			heredoc_exec(t_data *data);
int			expand_heredoc(char **line, t_data *data);
int			heredoc_execution(t_data *data, t_tkn *tkn);
int			open_heredocs(t_data *data);
int			heredoc(t_data *data, t_tkn *hrdc, int i);
int			count_heredocs(t_data *data);
int			builtin_call(t_data *data, t_tkn *cmd);
int			is_builtin(t_tkn *tkn);

char		*get_path(t_env *env);
int			path_join(char *cmd, char *path, char **res);
int			is_valid_exec(char *path);
int			print_err(char *s);
char		*get_cmd(t_tkn *cmd);
void		tkn_cleanup(t_tkn *tkn_list, char **cmd);
void		cleanup(t_data *data, char **cmd);
int			is_builtin(t_tkn *tkn);
int			red_in_out(t_tkn *cmd);

#endif