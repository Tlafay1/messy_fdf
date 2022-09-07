/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:01:30 by tlafay            #+#    #+#             */
/*   Updated: 2021/11/10 15:46:19 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	temp;
	int		i;

	i = 0;
	temp.next = lst;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
