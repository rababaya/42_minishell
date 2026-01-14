/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 10:21:52 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/14 14:56:16 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

int		execution(t_data *data, t_tkn *cmd);
int		child_process(t_data *data, t_tkn *cmd);
int		redirection(t_data *data, t_tkn *cmd);
t_tkn	*next_pipe(t_tkn *tkn);
int		pipes(t_data *data, t_tkn *tkn);
int		arg_len(t_tkn *tkn);
int		heredoc_exec(t_data *data);
int		expand_heredoc(char **line, t_data *data);
int		heredoc_execution(t_data *data);
int		heredoc(t_data *data, t_tkn *hrdc);

#endif