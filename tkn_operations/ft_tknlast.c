/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tknlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:53:26 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/16 17:30:09 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn	*ft_tknlast(t_tkn *tkn)
{
	if (!tkn)
		return (NULL);
	while (tkn->next)
		tkn = tkn->next;
	return (tkn);
}
