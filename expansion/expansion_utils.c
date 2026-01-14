/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:02:02 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/14 14:51:20 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varname_len(char *tkn)
{
	int	len;

	len = 0;
	if (tkn[len] == '?')
		return (1);
	if (!tkn[len] || (!ft_isalpha(tkn[len]) && tkn[len] != '_'))
		return (0);
	while (tkn[len] && (ft_isalnum(tkn[len]) || tkn[len] == '_'))
		len++;
	return (len);
}
