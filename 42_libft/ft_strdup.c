/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:25:33 by rababaya          #+#    #+#             */
/*   Updated: 2025/01/24 14:36:56 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	void	*cpy;
	size_t	len;

	len = ft_strlen(s1);
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	((char *)cpy)[len] = '\0';
	return ((char *)ft_memcpy(cpy, s1, len));
}
