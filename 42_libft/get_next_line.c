/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:16:01 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/17 16:05:08 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char *res, char *buff)
{
	char	*ret;

	if (!res)
	{
		res = malloc(1 * sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
	}
	ret = ft_strjoin(res, buff);
	if (!ret)
	{
		free(res);
		return (NULL);
	}
	free(res);
	return (ret);
}

static char	*dif(char *buff)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	line = malloc(ft_strlen(buff) - i * sizeof(char));
	if (!line)
	{
		free(buff);
		return (NULL);
	}
	i++;
	j = 0;
	while (buff[i])
		line[j++] = buff[i++];
	line[j] = '\0';
	free(buff);
	return (line);
}

static char	*buffer_line(char *res, int fd)
{
	int		count;
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	count = read(fd, buff, BUFFER_SIZE);
	while (count > 0)
	{
		buff[count] = '\0';
		res = join(res, buff);
		if (!res)
			return (free(buff), NULL);
		if (ft_strchr(buff, '\n'))
			break ;
		count = read (fd, buff, BUFFER_SIZE);
	}
	free(buff);
	if (count < 0 || !res || !*res)
		return (free(res), NULL);
	return (res);
}

static char	*clear_line(char *buff)
{
	int		count;
	char	*res;

	count = 0;
	while (buff[count] && buff[count] != '\n')
		count++;
	if (buff[count] == '\n')
		res = malloc(count + 2 * sizeof(char));
	else
		res = malloc(count + 1 * sizeof(char));
	if (!res)
		return (NULL);
	count = 0;
	while (buff[count] && buff[count] != '\n')
	{
		res[count] = buff[count];
		count++;
	}
	if (buff[count] == '\n')
		res[count++] = '\n';
	res[count] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buff[533];
	char		*res;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff[fd] = buffer_line(buff[fd], fd);
	if (!buff[fd])
		return (NULL);
	res = clear_line(buff[fd]);
	if (!res)
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	buff[fd] = dif(buff[fd]);
	if (!buff[fd] || !*buff[fd])
	{
		free(buff[fd]);
		buff[fd] = NULL;
	}
	return (res);
}
