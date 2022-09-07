/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rolled.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:17:04 by tlafay            #+#    #+#             */
/*   Updated: 2022/03/17 11:20:25 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <X11/keysym.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <sys/time.h>
# include "mlx.h"
# include "../srcs/libft/libft.h"
#define G 9.81
#define ESCAPE_KEY 53
#define WIDTH 1920
#define HEIGHT 1080
#define FD 124
#define FG 123
#define FH 126
#define FB 125
#define X_UP 91
#define X_DOWN 84
#define Y_UP 86
#define Y_DOWN 88
#define Z_UP 69
#define Z_DOWN 78
#define W 13
#define S 1
#define A 0
#define D 2

typedef struct	s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct	s_win
{
	void	*mlx;
	void	*win;
}				t_win;

typedef struct s_point
{
	double x, y, z;
	int exists;
}				t_point;

typedef struct s_test
{
	t_win main;
	t_image img;
	struct timeval start;
}				t_test;

typedef struct s_vector
{
	t_point	p1;
	t_point	p2;
	double	norm;
	double	dx;
	double	dy;
	double	dz;
	double	sx;
	double	sy;
	double	sz;
	double	dm;
}				t_vector;

t_image	draw_cube(t_image img, long time);
t_image draw_ball(int x_mid, int y_mid, int r, t_image img);

int	key_hook(int keycode, t_test *test)
{
	if (keycode == ESCAPE_KEY)
	{
		exit(0);
	}
	return (0);
}

int	exit_hook(int keycode, t_win *main)
{
	exit(0);
}

int render_next_frame(t_test *test)
{
	t_image 		new_img;
	struct timeval	end;
	long			time;

	gettimeofday(&end, NULL);
	time = ((end.tv_sec * 1000000 + end.tv_usec) - (test->start.tv_sec * 1000000 + test->start.tv_usec));
	new_img.img = mlx_new_image(test->main.mlx, WIDTH, HEIGHT);
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length,
					&new_img.endian);
	mlx_destroy_image(test->main.mlx, test->img.img);
	test->img = draw_cube(new_img, time);
	mlx_put_image_to_window(test->main.mlx, test->main.win, new_img.img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
		if (y0 + ref.y >= 0 && y0 + ref.y < HEIGHT && x0 + ref.x >= 0 && x0 + ref.x < WIDTH)
			my_mlx_pixel_put(&img, x0 + ref.x, y0 + ref.y, 0x00FF0000);
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

void	circle_coord(double *x, double *y, int r, double angle)
{
	double tmp_x = *x;
	double tmp_y = *y;

	*x = tmp_x + (cos(4.712388 - angle) * r);
	*y = tmp_y - (sin(4.712388 - angle) * r);
}

double coeff_dir(t_point p1, t_point p2)
{
	return ((p2.y - p1.y) / (p2.x - p1.x));
}

double calc_y(double x, t_point p1, t_point p2)
{
	double	a;
	double	b;

	a = coeff_dir(p1, p2);
	b = p1.y - (a * p1.x);
	return (a * x + b);
}

t_image	draw_cube(t_image img, long time)
{
	t_point		p1, p2, l1, l2;
	t_vector	v;
	double		x_circle, y_circle;

	int r = 10;
	init_point(&p1, 200, 200, 0);
	init_point(&p2, 1000, 1000, 0);
	x_circle = p2.x;
	y_circle = p2.y;
	v = init_vector(p1, p2);
	img = join_points(p1, p2, img);
	double angle = asin((p2.y - p1.y) / v.norm);
	circle_coord(&x_circle, &y_circle, r, angle);
	draw_ball(x_circle, y_circle, r, img);
	return (img);
}

t_image draw_ball(int x_mid, int y_mid, int r, t_image img)
{
	int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
	do
	{
		my_mlx_pixel_put (&img, x_mid-x, y_mid+y, 0x00FF0000); /*   I. Quadrant */
		my_mlx_pixel_put (&img, x_mid-y, y_mid-x, 0x00FF0000); /*  II. Quadrant */
		my_mlx_pixel_put (&img, x_mid+x, y_mid-y, 0x00FF0000); /* III. Quadrant */
		my_mlx_pixel_put (&img, x_mid+y, y_mid+x, 0x00FF0000); /*  IV. Quadrant */
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