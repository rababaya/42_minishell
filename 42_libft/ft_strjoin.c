/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:30:57 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/11 14:52:14 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*res;
	char	*start;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
	{
		return (NULL);
	}
	start = res;
	if (s1)
		while (*s1)
			*(res++) = *(s1++);
	if (s2)
		while (*s2)
			*(res++) = *(s2++);
	*res = '\0';
	return (start);
}
