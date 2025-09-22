/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:40:11 by rababaya          #+#    #+#             */
/*   Updated: 2025/09/22 18:37:51 by rababaya         ###   ########.fr       */
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

void	ft_echo(char **args)
{
	int	i;
	int	nl;
	int	is_printed;

	i = 1;
	is_printed = 0;
	nl = 1;
	while (args[i])
	{
		if (is_newline(args[i]) && !is_printed)
		{
			nl = 0;
			i++;
			continue ;
		}
		print(args[i]);
		if (args[i + 1])
			print(" ");
		is_printed = 1;
		i++;
	}
	if (nl)
		print("\n");
}
