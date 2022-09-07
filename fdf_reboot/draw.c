/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:43:12 by tlafay            #+#    #+#             */
/*   Updated: 2022/01/14 14:02:05 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_image	plot_line(t_vector vector, t_image img, t_point ref)
{
	int			err;

	err = vector.dx + vector.dy;
	while (1)
	{
		if (vector.p1.y + ref.y >= 0 && vector.p1.y + ref.y < HEIGHT
			&& vector.p1.x + ref.x >= 0 && vector.p1.x + ref.x < WIDTH)
			my_mlx_pixel_put(&img, vector.p1.x
				+ ref.x, vector.p1.y + ref.y, 0x00FFFFFF);
		if (vector.p1.x == vector.p2.x && vector.p1.y == vector.p2.y)
			break ;
		vector.e2 = 2 * err;
		if (vector.e2 >= vector.dy)
		{
			err += vector.dy;
			vector.p1.x += vector.sx;
		}
		if (vector.e2 <= vector.dx)
		{
			err += vector.dx;
			vector.p1.y += vector.sy;
		}
	}
	return (img);
}

t_image	join_points(t_point *points, t_image img, t_system system)
{
	int	i;

	i = 0;
	while (points[i].exists)
	{
		if (i + 1 < system.width * system.height
			&& (i + 1) % system.width != 0)
		{
			img = plot_line(init_vector(points[i],
						points[i + 1]), img, system.ref);
		}
		if (i + system.width < system.width * system.height)
		{
			img = plot_line(init_vector(points[i],
						points[i + system.width]), img, system.ref);
		}
		i++;
	}
	free(points);
	return (img);
}

t_point	*project_points(t_point *map, int proj)
{
	t_point	*ret;
	int		i;

	i = 0;
	ret = (t_point *)malloc((point_len(map) + 1) * sizeof(t_point));
	while (map[i].exists)
	{
		if (proj == 1)
		{
			ret[i].x = sqrt(2) / 2 * (map[i].x - map[i].y);
			ret[i].y = sqrt(2.0 / 3.0) * map[i].z
				- 1 / sqrt(6) * (map[i].x + map[i].y);
			ret[i].exists = 1;
		}
		else
		{
			ret[i].x = -map[i].x + 0.5 * map[i].z * cos(M_PI / 2);
			ret[i].y = map[i].y + 0.5 * map[i].z * sin(M_PI / 2);
			ret[i].exists = 1;
		}
		i++;
	}
	ret[i].exists = 0;
	return (ret);
}

t_point	*pointcpy(t_system system)
{
	t_point	*ret;
	int		i;

	i = 0;
	ret = (t_point *)malloc((point_len(system.map) + 1) * sizeof(t_point));
	while (system.map[i].exists)
	{
		ret[i].x = (system.map[i].x - system.width / 2) * system.norm;
		ret[i].y = (system.map[i].y - system.height / 2) * system.norm;
		ret[i].z = system.map[i].z * 0.2 * system.norm;
		ret[i].exists = 1;
		i++;
	}
	ret[i].exists = 0;
	return (ret);
}

t_image	draw_frame(t_image img, t_system system, int proj)
{
	t_point	*map;

	map = pointcpy(system);
	map = rotate_z(map, system.k);
	map = rotate_y(map, system.j);
	map = rotate_x(map, system.i);
	img = join_points(project_points(map, proj), img, system);
	free(map);
	return (img);
}
