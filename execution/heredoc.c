/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 22:09:56 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/10 16:59:21 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculate(char *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (*str)
	{
		if ((*str == '\'' && !quote) || (*str == '\"' && !quote))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			len++;
		str++;
	}
	if (quote)
		return (-1);
	return (len);
}

char	*dequote(char *str, int len)
{
	char	*res;
	int		i;
	char	*tmp;
	char	quote;

	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	quote = 0;
	tmp = str;
	while (*str)
	{
		if ((*str == '\'' && !quote) || (*str == '\"' && !quote))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			res[i++] = *str;
		str++;
	}
	free(tmp);
	res[i] = 0;
	return (res);
}

int	heredoc_cycle(t_data *data, const char *eof, int fd[2], int expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_sig_status == 130)
		{
			if (line)
				free(line);
			break ;
		}
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
			if (expand_heredoc(&line, data->env_list))
				return (close(fd[0]), close(fd[1]), 1);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	return (0);
}

int	heredoc(t_data *data, t_tkn *hr)
{
	char	*eof;
	int		fd[2];
	int		expand;

	expand = 1;
	if (!hr->next || hr->next->type != ARG)
		return (2);
	if (ft_strchr(hr->next->token, '\'') || ft_strchr(hr->next->token, '\"'))
		expand = 0;
	if (calculate(hr->next->token) < 0)
		return (2);
	hr->next->token = dequote(hr->next->token, calculate(hr->next->token));
	if (hr->next->token == NULL)
		return (1);
	eof = hr->next->token;
	if (data->heredoc_fd != -1)
		close(data->heredoc_fd);
	if (pipe(fd) == -1)
		return (perror("minishell: heredoc"), 1);
	g_sig_status = 0;
	if (heredoc_cycle(data, eof, fd, expand))
		return (1);
	close(fd[1]);
	data->heredoc_fd = fd[0];
	return (0);
}

int	heredoc_execution(t_data *data)
{
	if (data->heredoc_fd == -1)
		return (0);
	if (dup2(data->heredoc_fd, STDIN_FILENO) < 0)
		return (close(data->heredoc_fd), 1);
	close(data->heredoc_fd);
	return (0);
}
