/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:15:38 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/11 15:00:48 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	return (write (1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		i++;
	}
	return (write (1, str, i));
}

int	ft_puthex(unsigned long n, char mode)
{
	int	count;

	count = 0;
	if (n > 15)
	{
		count += ft_puthex(n / 16, mode);
		n %= 16;
	}
	if (n > 9)
		count += ft_putchar(n - 10 + mode - 23);
	else
		count += ft_putchar(n + 48);
	return (count);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		count += ft_putnbr(n / 10);
		n %= 10;
	}
	count += ft_putchar(n + 48);
	return (count);
}

int	ft_putunsigned_nbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
	{
		count += ft_putunsigned_nbr(n / 10);
		n %= 10;
	}
	count += ft_putchar(n + 48);
	return (count);
}
