/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 22:09:56 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/05 19:40:45 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_data *data, t_tkn *hrdc)
{
	char	*eof;
	char	*line;
	int		fd[2];
	// int		expand;
	
	if (!hrdc->next || hrdc->next->type != ARG)
		return (1);
	eof = hrdc->next->token;
	if (data->heredeoc_fd != -1)
		close(data->heredeoc_fd);
	if (pipe(fd) == -1)
		return (perror("minishell: heredoc"), 1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(line);
			break;
		}
		// if (is_quoted(eof))
		// 	expand = 0;
		// expanded = expand_heredoc(line);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		// free(expanded);
	}
	close(fd[1]);
	data->heredeoc_fd = fd[0];
	// free(hrdc->token);
	return (0);
}
