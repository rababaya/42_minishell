/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:18:56 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/17 18:20:22 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(t_tkn *cmd)
{
	while (cmd && cmd->type != PIPE)
	{
		if (cmd->type != ARG)
			cmd = cmd->next->next;
		else
			return (cmd->token);
	}
	return (NULL);
}

char	*get_path(t_env *env)
{
	if (!env)
		return (NULL);
	while (env && ft_strncmp(env->key, "PATH", 5))
		env = env->next;
	if (!env)
		return (NULL);
	return (env->value);
}

int	path_join(char *cmd, char *path, char **res)
{
	int	len;
	int	i;

	len = ft_strlen(path) + ft_strlen(cmd) + 1;
	if (ft_strlen(path) && path[ft_strlen(path) - 1] != '/')
		len++;
	*res = (char *)malloc(len);
	if (!*res)
		return (1);
	i = 0;
	while (*path)
		(*res)[i++] = *(path++);
	if (*(path - 1) != '/')
		(*res)[i++] = '/';
	while (*cmd)
	{
		(*res)[i++] = *(cmd++);
	}
	(*res)[i] = 0;
	return (0);
}

int	is_valid_exec(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (errno);
	if (!S_ISREG(st.st_mode))
		return (126);
	if (access(path, X_OK) != 0)
		return (errno);
	return (0);
}

int	print_err(char *s)
{
	char	*str;
	int		len;

	len = ft_strlen(s);
	str = (char *)malloc(32 + len);
	if (!str)
		return (1);
	ft_memcpy(str, "minishell: ", 11);
	ft_memcpy(str + 11, s, len);
	ft_memcpy(str + 11 + len, ": command not found\n", 20);
	str[31 + len] = 0;
	write(2, str, len + 31);
	free(str);
	return (0);
}
