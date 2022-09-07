/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rolled.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:17:04 by tlafay            #+#    #+#             */
/*   Updated: 2022/03/18 16:40:36 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rolled.h"

t_image	plot_line (t_point p0, t_point p1, t_image img, t_point ref)
{
	int x0 = p0.x;
	int x1 = p1.x;
	int y0 = p0.y;
	int y1 = p1.y;
	int dx =  abs (x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0);
	int sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy;
	int e2;
	double z_max = 200;
 
	for (;;)
	{
		if (invert_y(y0 + ref.y) >= 0 && invert_y(y0 + ref.y) < HEIGHT && x0 + ref.x >= 0 && x0 + ref.x < WIDTH)
			my_mlx_pixel_put(&img, x0 + ref.x, invert_y(y0 + ref.y), 0x00FF0000);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
	return (img);
}

t_image	join_points(t_point p1, t_point p2, t_image img)
{
	t_point ref;

	init_point(&ref, 0, 0, 0);
	img = plot_line(p1, p2, img, ref);
	return (img);
}

static double	ft_abs(double a)
{
	if (a > 0)
		return (a);
	else
		return (-a);
}

t_image	draw_cube(t_image img, double time)
{
	t_point		p1, p2, l1, l2;
	t_vector	v;
	double		x_circle, y_circle, angle;

	int r = 10;
	init_point(&p1, 0, 0, 0);
	init_point(&p2, 1920, 1080, 0);
	v = init_vector(p1, p2);
	img = join_points(p1, p2, img);
	angle = asin((p1.y - p2.y) / v.norm);
	x_circle = trajectory(time, angle, G, p1.x);
	y_circle = calc_y(x_circle, p2, p1);
	circle_coord(&x_circle, &y_circle, r, angle);
	draw_ball(x_circle, y_circle, r, img);
	return (img);
}

t_image draw_ball(int x_mid, int y_mid, int r, t_image img)
{
	int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
	do
	{
		if (x_mid - x > 0 && x_mid - x < WIDTH && invert_y(y_mid + y) > 0 && invert_y(y_mid + y) < HEIGHT)
			my_mlx_pixel_put (&img, x_mid - x, invert_y(y_mid + y), 0x00FF0000); /*   I. Quadrant */
		
		if (x_mid - y > 0 && x_mid - y < WIDTH && invert_y(y_mid - x) > 0 && invert_y(y_mid - x) < HEIGHT)
			my_mlx_pixel_put (&img, x_mid - y, invert_y(y_mid - x), 0x00FF0000); /*  II. Quadrant */
		
		if (x_mid + x > 0 && x_mid + x < WIDTH && invert_y(y_mid - y) > 0 && invert_y(y_mid - y) < HEIGHT)
			my_mlx_pixel_put (&img, x_mid + x, invert_y(y_mid - y), 0x00FF0000); /* III. Quadrant */
		
		if (x_mid + y > 0 && x_mid + y < WIDTH && invert_y(y_mid + x) > 0 && invert_y(y_mid + x) < HEIGHT)
			my_mlx_pixel_put (&img, x_mid + y, invert_y(y_mid + x), 0x00FF0000); /*  IV. Quadrant */
		
		r = err;
		if (r >  x) err += ++x*2+1; /* e_xy+e_x > 0 */
		if (r <= y) err += ++y*2+1; /* e_xy+e_y < 0 */
	}
	while (x < 0);
	return (img);
}

int	main(int argc, char **argv)
{
	t_win	main;
	char	**tab;
	t_image img;
	t_test test;

	main.mlx = mlx_init();

	img.img = mlx_new_image(main.mlx, 1920, 1080);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	if (main.mlx == 0)
		exit(0);
	main.win = mlx_new_window(main.mlx, WIDTH, HEIGHT, "cube.c");

	mlx_hook(main.win, 17, 1L<<17, exit_hook, (void *)0);

	mlx_key_hook(main.win, key_hook, (void *)0);

	test.main = main;
	test.img = img;

	gettimeofday(&test.start, NULL);
	mlx_loop_hook(main.mlx, render_next_frame, &test);

	mlx_loop(main.mlx);
}