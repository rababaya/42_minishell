/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   punctuation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:05:50 by rababaya          #+#    #+#             */
/*   Updated: 2026/01/14 14:44:04 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_punctuation(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (!*str)
				return (0);
		}
		else if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
				str++;
			if (!*str)
				return (0);
		}
		str++;
	}
	return (1);
}
