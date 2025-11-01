/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <dgrigor2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:40:11 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/01 17:05:13 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_newline(char	*str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

int	ft_echo(char **args)
{
	int	i;
	int	nl;
	int	is_printed;

	i = 0;
	is_printed = 0;
	nl = 1;
	while (args[++i])
	{
		if (is_newline(args[i]) && !is_printed)
		{
			nl = 0;
			continue ;
		}
		if (print(args[i]) < 0)
			return (1);
		if (args[i + 1])
			if (print(" "))
				return (1);
		is_printed = 1;
	}
	if (nl)
		if (print("\n"))
			return (1);
	return (0);
}
