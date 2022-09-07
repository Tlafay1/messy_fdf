/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:41:36 by tlafay            #+#    #+#             */
/*   Updated: 2021/12/02 15:22:39 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**********************************************
**
**	Fonctions à faire pour libft:
**		char *ft_strccut(char *str, char cut)
**		
**
**********************************************
*/

#include "ft_printf.h"
#include <limits.h>

void	ft_putuint(unsigned int nb, int *count)
{
	unsigned int	s;

	s = nb;
	if (s > 9)
		ft_putnbr(s / 10, count);
	ft_putchar((s % 10) + '0');
	(*count)++;
}

void	ft_putptr(unsigned long long ptr, int *count)
{
	unsigned long long	s;
	char				*base;

	s = 0;
	base = "0123456789abcdef";
	if (ptr >= 0)
		s = ptr;
	if (ptr < 0)
	{
		s = -ptr;
		ft_putchar('-');
		(*count)++;
	}
	if (s > 15)
	{
		ft_putptr(s / 16, count);
		ft_putptr(s % 16, count);
	}
	else
	{
		ft_putchar(base[s]);
		(*count)++;
	}
}

void	foret_de_if(char format, int *count, va_list args)
{
	if (format == 'c')
		*count += ft_putchar(va_arg(args, int));
	else if (format == 's')
		*count += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
	{
		*count += ft_putstr("0x");
		ft_putptr(va_arg(args, unsigned long long), &(*count));
	}
	else if (format == 'i' || format == 'd')
		ft_putnbr(va_arg(args, int), &(*count));
	else if (format == 'u')
		ft_putuint(va_arg(args, unsigned int), &(*count));
	else if (format == 'x')
		ft_puthexa(va_arg(args, unsigned long long),
			"0123456789abcdef", &(*count));
	else if (format == 'X')
		ft_puthexa(va_arg(args, unsigned long long),
			"0123456789ABCDEF", &(*count));
	else if (format == '%')
		*count += ft_putchar('%');
	else
		*count += ft_putchar(format);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			foret_de_if(*format, &count, args);
		}
		else
			count += ft_putchar(*format);
		format++;
	}
	return (count);
}
