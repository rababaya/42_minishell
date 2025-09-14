/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:31:48 by rababaya          #+#    #+#             */
/*   Updated: 2025/01/29 14:55:20 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	lenght;
	char	*res;

	lenght = ft_strlen(s);
	if (len + start > lenght)
		len = lenght - start;
	if (start >= lenght || !s)
		return (ft_strdup(""));
	i = 0;
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	while (i < len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
