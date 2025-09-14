/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:22:38 by rababaya          #+#    #+#             */
/*   Updated: 2025/01/23 19:28:10 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = ft_strlen(src);
	while (*dest)
	{
		dest++;
		i++;
	}
	if (dstsize == 0 || dstsize <= i)
		return (dstsize + j);
	k = 0;
	while (*src && k < dstsize - i - 1)
	{
		*dest = *src;
		dest++;
		src++;
		k++;
	}
	*dest = '\0';
	return (i + j);
}
