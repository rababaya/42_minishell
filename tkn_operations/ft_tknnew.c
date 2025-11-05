/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tknnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:03:53 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/16 17:14:27 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn	*ft_tknnew(char *token, int type)
{
	t_tkn	*new;

	if (!token)
		return (NULL);
	new = (t_tkn *)malloc(sizeof(t_tkn));
	if (!new)
		return (NULL);
	new->token = token;
	new->type = type;
	new->next = NULL;
	return (new);
}
