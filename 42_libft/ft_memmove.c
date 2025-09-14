/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:45:36 by rababaya          #+#    #+#             */
/*   Updated: 2025/01/23 14:36:40 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*iter_dest;

	if (dest != src && n)
	{
		iter_dest = (unsigned char *)dest;
		if (dest < src)
			while (n--)
				*iter_dest++ = *(const unsigned char *)src++;
		else
		{
			iter_dest += n;
			src = (const unsigned char *)src + n;
			while (n--)
				*--iter_dest = *(const unsigned char *)--src;
		}
	}
	return (dest);
}
