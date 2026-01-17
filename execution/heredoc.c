/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 22:09:56 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 15:25:03 by rababaya         ###   ########.fr       */
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
		if (!line)
		{
			data->exit_status = -1;
			return (1);
		}
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
			if (expand_heredoc(&line, data))
				return (1);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	return (0);
}

int	heredoc(t_data *data, t_tkn *hr, int i)
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
	if (pipe(fd) == -1)
		return (perror("minishell: heredoc"), 1);
	g_sig_status = 0;
	setup_heredoc_signals();
	if (heredoc_cycle(data, eof, fd, expand))
		return (close(fd[1]), (data->hrdc)[i].fd = fd[0], 1);
	close(fd[1]);
	(data->hrdc)[i].fd = fd[0];
	return (0);
}
