/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:28:42 by rababaya          #+#    #+#             */
/*   Updated: 2025/10/03 00:18:08 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_my_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new;
	size_t	copy_size;

	new = malloc(new_size);
	if (!new)
		return (free(ptr), NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new, ptr, copy_size);
	free(ptr);
	return (new);
}
