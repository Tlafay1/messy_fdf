/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:39:29 by tlafay            #+#    #+#             */
/*   Updated: 2021/12/16 08:33:56 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coordinates.h"

/***
	These functions are used to translate each point of a system using an angle.
	For that, we use the current system and change
	the coordinates of all the points in it.
	Conversion matrix formulas found at
	https://stackoverflow.com/questions/14607640/rotating-a-vector-in-3d-space
***/

void	rotate_x(t_point **point, double angle)
{
	int		i;
	double	y_tmp;
	double	z_tmp;

	i = 0;
	y_tmp = point[i]->y;
	z_tmp = point[i]->z;
	while (point[i]->exists)
	{
		y_tmp = point[i]->y * cos(angle) - point[i]->z * sin(angle);
		z_tmp = point[i]->y * sin(angle) + point[i]->z * cos(angle);
		point[i]->y = y_tmp;
		point[i]->z = z_tmp;
		i++;
	}
}

void	rotate_y(t_point **point, double angle)
{
	int		i;
	double	x_tmp;
	double	z_tmp;

	i = 0;
	x_tmp = point[i]->x;
	z_tmp = point[i]->z;
	while (point[i]->exists)
	{
		x_tmp = point[i]->x * cos(angle) + point[i]->z * sin(angle);
		z_tmp = - (point[i]->x * sin(angle)) + point[i]->z * cos(angle);
		point[i]->x = x_tmp;
		point[i]->z = z_tmp;
		i++;
	}
}

void	rotate_z(t_point **point, double angle)
{
	int		i;
	double	x_tmp;
	double	y_tmp;

	i = 0;
	x_tmp = point[i]->x;
	y_tmp = point[i]->y;
	while (point[i]->exists)
	{
		x_tmp = point[i]->x * cos(angle) - point[i]->y * sin(angle);
		y_tmp = point[i]->x * sin(angle) + point[i]->y * cos(angle);
		point[i]->x = x_tmp;
		point[i]->y = y_tmp;
		i++;
	}
}
