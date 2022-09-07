/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:42:01 by tlafay            #+#    #+#             */
/*   Updated: 2021/12/02 14:27:11 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_strlen(char *str);
int		ft_putchar(char c);
int		ft_putstr(char *str);
void	ft_putnbr(int nb, int *count);
void	ft_putuint(unsigned int nb, int *count);
void	ft_putptr(unsigned long long ptr, int *count);
void	ft_puthexa(unsigned int nbr, char *base, int *count);
int		ft_printf(const char *format, ...);

#endif