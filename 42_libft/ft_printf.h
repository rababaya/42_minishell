/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:18:40 by rababaya          #+#    #+#             */
/*   Updated: 2025/02/03 16:42:52 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int	check_type(va_list print, char type);
int	ft_printf(const char *str, ...);
int	ft_putchar(int c);
int	ft_puthex(unsigned long n, char mode);
int	ft_putnbr(int n);
int	ft_putunsigned_nbr(unsigned int n);
int	ft_putstr(char *str);

#endif
