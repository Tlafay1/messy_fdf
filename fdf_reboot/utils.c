/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:44:07 by tlafay            #+#    #+#             */
/*   Updated: 2022/01/13 11:04:58 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_point(t_point *point, double x, double y, double z)
{
	point->x = x;
	point->y = y;
	point->z = z;
	point->exists = 1;
}

static int	compare(int x, int y)
{
	if (x < y)
		return (1);
	else
		return (-1);
}

static int	ft_abs(double a)
{
	if (a > 0)
		return (a);
	else
		return (-a);
}

t_vector	init_vector(t_point	p1, t_point	p2)
{
	t_vector	vector;

	vector.p1.x = (int)p1.x;
	vector.p1.y = (int)p1.y;
	vector.p2.x = (int)p2.x;
	vector.p2.y = (int)p2.y;
	vector.norm = sqrt(pow(vector.p2.x - vector.p1.x, 2)
			+ pow(vector.p2.y - vector.p1.y, 2)
			+ pow(vector.p2.z - vector.p1.z, 2));
	vector.dx = ft_abs(vector.p2.x - vector.p1.x);
	vector.sx = compare(vector.p1.x, vector.p2.x);
	vector.dy = -ft_abs(vector.p2.y - vector.p1.y);
	vector.sy = compare(vector.p1.y, vector.p2.y);
	vector.dz = ft_abs(vector.p2.z - vector.p1.z);
	vector.sz = compare(vector.p1.z, vector.p2.z);
	return (vector);
}
