/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 22:09:56 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/15 14:33:11 by dgrigor2         ###   ########.fr       */
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
			if (expand_heredoc(&line, data))
				return (close(fd[0]), close(fd[1]), 1);
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
	if (heredoc_cycle(data, eof, fd, expand))
		return (1);
	close(fd[1]);
	(data->hrdc)[i].fd = fd[0];
	return (0);
}

t_tkn	*get_last_tkn(t_tkn *tkn)
{
	while (tkn && tkn->type != PIPE)
		tkn = tkn->next;
	return (tkn);
}

int	is_last_hrdc(t_tkn *tkn)
{
	tkn = tkn->next;
	while (tkn && tkn->type != PIPE)
	{
		if (tkn->type == HRDC)
			return (0);
		tkn = tkn->next;
	}
	return (1);
}

int	get_proper_fd(t_data *data, t_tkn *tkn)
{
	int		i;
	t_tkn	*last;

	i = 0;
	last = get_last_tkn(tkn);
	while ((data->hrdc)[i].tkn != last)
		i++;
	return ((data->hrdc)[i].fd);
}

int	heredoc_execution(t_data *data, t_tkn *tkn)
{
	int	fd;

	if (!is_last_hrdc(tkn))
		return (0);
	fd = get_proper_fd(data, tkn);
	if (fd == 0)
		return (0);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), errno);
	close(fd);
	return (0);
}
