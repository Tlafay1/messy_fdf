/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:41:06 by tlafay            #+#    #+#             */
/*   Updated: 2022/01/14 12:05:55 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup2(s2));
	ret = (char *)malloc((ft_strlen2(s1) + ft_strlen2(s2) + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ft_free(s1);
	ret[i + j] = '\0';
	return (ret);
}

char	*ft_strdup2(char *src)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)malloc(ft_strlen2(src) + 1);
	if (!ret)
		return (NULL);
	while (src[i])
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	ft_strlen2(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_strcpy2(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s2)
	{
		while (s1[i])
		{
			s1[i] = '\0';
			i++;
		}
	}
	else
	{
		while (s2[i])
		{
			s1[i] = s2[i];
			i++;
		}
		s1[i] = '\0';
	}
}
