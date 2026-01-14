/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:05 by dgrigor2          #+#    #+#             */
/*   Updated: 2026/01/14 14:38:13 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenise(t_tkn **tkn, char *str)
{
	t_tkn	*buf;

	while (*str)
	{
		if (is_red(str))
		{
			buf = tkn_red(&str);
			if (!buf)
				return (ft_tknclear(tkn), -1);
			ft_tknadd_back(tkn, buf);
		}
		else if (ft_iswhitespace(*str))
			str++;
		else
		{
			buf = tkn_arg(&str);
			if (!buf)
				return (ft_tknclear(tkn), -1);
			ft_tknadd_back(tkn, buf);
		}
	}
	return (0);
}
