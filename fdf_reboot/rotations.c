/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:28:44 by tlafay            #+#    #+#             */
/*   Updated: 2022/01/13 11:05:08 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_point	*rotate_x(t_point *point, double angle)
{
	int		i;
	double	y_tmp;
	double	z_tmp;

	i = 0;
	y_tmp = point[i].y;
	z_tmp = point[i].z;
	while (point[i].exists)
	{
		y_tmp = point[i].y * cos(angle) - point[i].z * sin(angle);
		z_tmp = point[i].y * sin(angle) + point[i].z * cos(angle);
		point[i].y = y_tmp;
		point[i].z = z_tmp;
		i++;
	}
	return (point);
}

t_point	*rotate_y(t_point *point, double angle)
{
	int		i;
	double	x_tmp;
	double	z_tmp;

	i = 0;
	x_tmp = point[i].x;
	z_tmp = point[i].z;
	while (point[i].exists)
	{
		x_tmp = point[i].x * cos(angle) + point[i].z * sin(angle);
		z_tmp = - (point[i].x * sin(angle)) + point[i].z * cos(angle);
		point[i].x = x_tmp;
		point[i].z = z_tmp;
		i++;
	}
	return (point);
}

t_point	*rotate_z(t_point *point, double angle)
{
	int		i;
	double	x_tmp;
	double	y_tmp;

	i = 0;
	x_tmp = point[i].x;
	y_tmp = point[i].y;
	while (point[i].exists)
	{
		x_tmp = point[i].x * cos(angle) - point[i].y * sin(angle);
		y_tmp = point[i].x * sin(angle) + point[i].y * cos(angle);
		point[i].x = x_tmp;
		point[i].y = y_tmp;
		i++;
	}
	return (point);
}

int	point_len(t_point *map)
{
	int	i;

	i = 0;
	while (map[i].exists)
		i++;
	return (i);
}
