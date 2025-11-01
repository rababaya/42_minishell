/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:42:18 by rababaya          #+#    #+#             */
/*   Updated: 2025/11/01 15:53:42 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_int(const char *str, int pm)
{
	if (pm == -1)
	{
		if ((ft_strlen(str) == 10 && ft_strncmp(str, "2147483648", 10) > 0)
			|| ft_strlen(str) > 10)
			return (0);
	}
	else
	{
		if ((ft_strlen(str) == 10 && ft_strncmp(str, "2147483647", 10) > 0)
			|| ft_strlen(str) > 10)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	pm;

	res = 0;
	i = 0;
	pm = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			pm = -pm;
		i++;
	}
	if (!is_in_int(&str[i], pm))
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (res * pm);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * pm);
}
