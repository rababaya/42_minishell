/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:49:02 by rababaya          #+#    #+#             */
/*   Updated: 2025/04/17 16:39:40 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	counter(const char *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	is_new;

	i = 0;
	count = 0;
	is_new = 1;
	while (s[i])
	{
		if (s[i] != c && is_new == 1)
		{
			is_new = 0;
			count++;
		}
		else if (s[i] == c && is_new == 0)
			is_new = 1;
		i++;
	}
	return (count);
}

static size_t	wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	free_split(char ***s, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free((*s)[i]);
		++i;
	}
	free(*s);
	*s = NULL;
	return ;
}

static char	**fill_split(char const *s, char c, char **res)
{
	size_t	i;
	size_t	j;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		j = wordlen(&s[i], c);
		res[count] = ft_substr(s, i, j);
		if (!res[count])
		{
			free_split(&res, i);
			return (NULL);
		}
		i = i + j;
		count++;
	}
	res[count] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**res;

	if (!s)
		return (NULL);
	count = counter(s, c);
	res = (char **)malloc(sizeof (char *) * (count + 1));
	if (!res)
		return (NULL);
	fill_split(s, c, res);
	free((void *)s);
	return (res);
}
/*
int main ()
{
	size_t i = 0;

	char **res = ft_split("      split       this for   me  !       ", ' ');
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
}*/
