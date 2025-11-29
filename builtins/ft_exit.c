/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:50:48 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/29 13:44:09 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in_longlong(const char *str, int pm)
{
	if (pm == -1)
	{
		if ((ft_strlen(str) == 19
				&& ft_strncmp(str, "9223372036854775808", 19) > 0)
			|| ft_strlen(str) > 19)
			return (0);
	}
	else
	{
		if ((ft_strlen(str) == 19
				&& ft_strncmp(str, "9223372036854775807", 19) > 0)
			|| ft_strlen(str) > 19)
			return (0);
	}
	return (1);
}

static int	is_numeric_arg(char *arg)
{
	int	i;
	int	pm;

	i = 0;
	pm = 1;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			pm = -pm;
		i++;
	}
	if (!arg[i])
		return (0);
	if (!is_in_longlong(&arg[i], pm))
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data)
{
	long long	exit_code;
	
	ft_putstr_fd("exit\n", 1);
	if (!data->args[1])
	{
		free_data(data);
		exit(0);
	}
	if (!is_numeric_arg(data->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(data->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_data(data);
		exit(255);
	}
	if (data->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(data->args[1]) % 256;
	free_data(data);
	exit(exit_code);
}
