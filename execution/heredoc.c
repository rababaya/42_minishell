/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 22:09:56 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/11 11:08:59 by dgrigor2         ###   ########.fr       */
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

int	heredoc(t_data *data, t_tkn *hrdc)
{
	char	*eof;
	char	*line;
	int		fd[2];
	int		expand;

	if (!hrdc->next || hrdc->next->type != ARG)
		return (2);
	expand = (ft_strchr(hrdc->next->token, '\'') || ft_strchr(hrdc->next->token, '\"')) ? 0 : 1;
	if (calculate(hrdc->next->token) < 0)
		return (2);
	hrdc->next->token = dequote(hrdc->next->token, calculate(hrdc->next->token));
	if (hrdc->next->token == NULL)
		return (1);
	eof = hrdc->next->token;
	if (data->in_fd != -1)
		close(data->in_fd);
	if (pipe(fd) == -1)
		return (perror("minishell: heredoc"), 1);
	g_sig_status = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || g_sig_status == 130)
		{
			if (line)
				free(line);
			break;
		}
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			free(line);
			break;
		}
		if (expand)
			if(expand_heredoc(&line, data->env_list))
				return (close(fd[0]), close(fd[1]), 1);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	// dup2(fd[0], STDIN_FILENO);
	data->in_fd = fd[0];
	return (0);
}

int heredoc_execution(t_data *data)
{
	if (data->in_fd == -1)
		return (0);
	if (dup2(data->in_fd, STDIN_FILENO) < 0)
		return (close(data->in_fd), 1);
	close(data->in_fd);
	return (0);
}
