/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:56:34 by rababaya          #+#    #+#             */
/*   Updated: 2025/04/21 17:23:45 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_counter(int n)
{
	size_t	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = len_counter(n);
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
	res[i--] = '\0';
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
	}
	while (n != 0)
	{
		res[i--] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
/*
int main()
{
	char *res = ft_itoa(-95);
    printf("%s",res);
}*/
