/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:14:29 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/11 14:45:49 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_type(va_list print, char type)
{
	int	count;

	count = 0;
	if (type == 'c')
		count += ft_putchar(va_arg(print, int));
	if (type == '%')
		count += ft_putchar('%');
	if (type == 's')
		count += ft_putstr(va_arg(print, char *));
	if (type == 'i' || type == 'd')
		count += ft_putnbr(va_arg(print, int));
	if (type == 'u')
		count += ft_putunsigned_nbr(va_arg(print, unsigned int));
	if (type == 'x' || type == 'X')
		count += ft_puthex(va_arg(print, unsigned int), type);
	if (type == 'p')
	{
		count += ft_putstr("0x");
		count += ft_puthex(va_arg(print, unsigned long), 'x');
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	print;
	int		count;

	count = 0;
	va_start (print, str);
	while (*str)
	{
		if (*str == '%')
			count += check_type(print, *++str);
		else
			count += write (1, str, 1);
		str++;
	}
	va_end (print);
	return (count);
}
