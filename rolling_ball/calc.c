/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:36:32 by tlafay            #+#    #+#             */
/*   Updated: 2022/03/18 13:08:37 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rolled.h"

void	circle_coord(double *x, double *y, int r, double angle)
{
	double tmp_x = *x;
	double tmp_y = *y;

	*x = *x - (cos(4.712388 - angle) * r);
	*y = *y - (sin(4.712388 - angle) * r);
}

double	coeff_dir(t_point p1, t_point p2)
{
	return ((p2.y - p1.y) / (p2.x - p1.x));
}

double	calc_y(double x, t_point p1, t_point p2)
{
	double	a;
	double	b;

	a = coeff_dir(p1, p2);
	b = p1.y - (a * p1.x);
	return (a * x + b);
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

static int ft_abs(double a)
{
	if (a > 0)
		return (a);
	else
		return (-a);
}

t_vector	init_vector(t_point	p1, t_point	p2)
{
	t_vector	vector;

	vector.p1 = p1;
	vector.p2 = p2;
	vector.norm = sqrt(pow(vector.p2.x - vector.p1.x, 2)
			+ pow(vector.p2.y - vector.p1.y, 2)
			+ pow(vector.p2.z - vector.p1.z, 2));
	vector.dx = ft_abs(vector.p2.x - vector.p1.x);
	vector.sx = compare(vector.p1.x, vector.p2.x);
	vector.dy = ft_abs(vector.p2.y - vector.p1.y);
	vector.sy = compare(vector.p1.y, vector.p2.y);
	vector.dz = ft_abs(vector.p2.z - vector.p1.z);
	vector.sz = compare(vector.p1.z, vector.p2.z);
	return (vector);
}

double	speed(double t, double angle, double v0)
{
	return ((/*((float)5 / 14) * */G * sin(angle) * t * 10)
		+ v0);
}

double	trajectory(double t, double angle, double v0, double x0)
{
	return ((((float)5 / 14) * G * sin(angle) * t * t * 100)
		+ v0 * t * 100 + x0);
}

int	invert_y(int y)
{
	y -= HEIGHT / 2;
	return (-y + HEIGHT / 2);
}
