/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:01:00 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/12/01 16:05:10 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char *file, char *path)
{
	char	*res;
	int		len;
	int		i;

	if (!path || !file || !*path || !*file)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(file) + 1;
	if (path[ft_strlen(path) - 1] != '/')
		len++;
	res = (char *)malloc(len);
	if (!res)
		return (NULL);
	i = 0;
	while (*path)
	{
		res[i++] = *(path++);
	}
	if (*(path - 1) != '/')
		res[i++] = '/';
	while (*file)
	{
		res[i++] = *(file++);
	}
	return (res);	
}

static char	*check_prog(char **paths, char *file)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(file, paths[i++]);
		if (!tmp)
			return (ft_free_mat(paths), NULL);
		if (!access(tmp, F_OK) && !access(tmp, X_OK))
			return (tmp);
		free(tmp);
	}
	return (NULL);
}

char	*set_to_path(char **envp, char *file)
{
	char	*tmp;
	char	**paths;

	if (!file || !*file)
		return (NULL);
	if (*file == '.' || *file == '/')
	{
		if (!access(file, F_OK) && !access(file, X_OK))
			return (file);
	}
	tmp = get_path(envp);
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (NULL);
	return (check_prog(paths, file));
}

char	*get_path(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 5))
			return (env->key);
		env = env->next;
	}
	return (NULL);
}

char	*ft_settopath(t_data *data)
{
	char	*path;

	if (*(data->args)[0] == '.' || *(data->args)[0] == '/')
		return (data->args[0]);
	path = 

}

int	execute(t_data *data)
{
	char	*path;

	path = ft_settopath(data);
}