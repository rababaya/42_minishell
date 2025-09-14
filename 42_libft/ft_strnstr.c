/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:58:20 by rababaya          #+#    #+#             */
/*   Updated: 2025/01/24 13:41:11 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!(*needle))
		return ((char *)str);
	while (*str && i < len)
	{
		if (!ft_strncmp(str, needle, ft_strlen(needle)))
			if (i + ft_strlen(needle) <= len)
				return ((char *)str);
		i++;
		str++;
	}
	return (NULL);
}
