/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:45:17 by tlafay            #+#    #+#             */
/*   Updated: 2021/12/08 16:14:23 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

void	ft_putnbr(int nb, int *count)
{
	unsigned int	s;

	s = 0;
	if (nb >= 0)
		s = nb;
	if (nb < 0)
	{
		s = nb * -1;
		ft_putchar('-');
		(*count)++;
	}
	if (s > 9)
		ft_putnbr(s / 10, count);
	ft_putchar((s % 10) + '0');
	(*count)++;
}

void	ft_puthexa(unsigned int nbr, char *base, int *count)
{
	unsigned int	s;

	s = 0;
	if (nbr >= 0)
		s = nbr;
	if (nbr < 0)
	{
		s = -nbr;
		ft_putchar('-');
		(*count)++;
	}
	if (s > 15)
	{
		ft_puthexa(s / 16, base, count);
		ft_puthexa(s % 16, base, count);
	}
	else
	{
		ft_putchar(base[s]);
		(*count)++;
	}
}
