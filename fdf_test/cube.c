/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:59:05 by tlafay            #+#    #+#             */
/*   Updated: 2022/01/12 08:41:08 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <X11/keysym.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include "mlx.h"
# include "../srcs/libft/libft.h"
# include <time.h>
#define ESCAPE_KEY 53
#define WIDTH 1920
#define HEIGHT 1080
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

t_image	draw_cube(t_image img, double i, double j, double k, t_point ref, double norm);

typedef	struct s_test
{
	t_image	img;
	t_win	main;
	double	i;
	double	j;
	double	k;
	double	norm;
	t_point ref;
	int modified;
}			t_test;

/***
	Rolling ball link :
	https://www.omnicalculator.com/physics/inclined-plane#rolling-ball
***/

int	key_hook(unsigned int keycode, t_test *test)
{
	if (keycode == ESCAPE_KEY)
	{
		mlx_destroy_window(test->main.mlx, test->main.win);
		exit(0);
	}
	if (keycode == X_UP)
		test->i += M_PI / 48;
	if (keycode == X_DOWN)
		test->i -= M_PI / 48;
	if (keycode == Y_UP)
		test->j += M_PI / 48;
	if (keycode == Y_DOWN)
		test->j -= M_PI / 48;
	if (keycode == Z_UP)
		test->k += M_PI / 48;
	if (keycode == Z_DOWN)
		test->k -= M_PI / 48;
	if (keycode == D)
		test->ref.x += 10;
	if (keycode == A)
		test->ref.x -= 10;
	if (keycode == W)
		test->ref.y -= 10;
	if (keycode == S)
		test->ref.y += 10;
	if (keycode == 15)
	{
		test->i = M_PI / 6;
		test->j = M_PI / 6;
		test->k = M_PI / 6;
		test->ref.x = WIDTH / 2;
		test->ref.y = HEIGHT / 2;
		test->norm = 200;
	}
	test->modified = 1;
	return (0);
}

int mouse_hook(int button, int x, int y, t_test *test)
{
	if (button == 4)
		test->norm += 10;
	if (button == 5 && test->norm >= 10)
		test->norm -= 10;
	test->modified = 1;
	return (0);
}

int	exit_hook(unsigned int keycode, t_win *main)
{
	exit(0);
}

int render_next_frame(t_test *test)
{
	t_image new_img;

	new_img.img = mlx_new_image(test->main.mlx, WIDTH, HEIGHT);
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length,
					&new_img.endian);
	mlx_destroy_image(test->main.mlx, test->img.img);
	if (test->i > M_PI * 2)
		test->i -= M_PI * 2;
	if (test->j > M_PI * 2)
		test->j -= M_PI * 2;
	if (test->k > M_PI * 2)
		test->k -= M_PI * 2;
	if (test->i < 0)
		test->i += M_PI * 2;
	if (test->j < 0)
		test->j += M_PI * 2;
	if (test->k < 0)
		test->k += M_PI * 2;
	new_img = draw_cube(new_img, test->i, test->j, test->k, test->ref, test->norm);
	mlx_put_image_to_window(test->main.mlx, test->main.win, new_img.img, 0, 0);
	test->img = new_img;
	test->modified = 0;
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

/*t_vector	init_vector(t_point	p1, t_point	p2)
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
}*/

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
			my_mlx_pixel_put(&img, x0 + ref.x, y0 + ref.y, 0x00FFFFFF);
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

t_image	join_points(t_point *points, t_image img, t_point ref)
{
	int i = 0;

	while (points[i].exists)
	{
		if (i + 1 < 9 && (i + 1) % 3 != 0)
			img = plot_line(points[i], points[i + 1], img, ref);
		if (i + 3 < 9)
			img = plot_line(points[i], points[i + 3], img, ref);
		i++;
	}
	return (img);
	//img = plot_line(points[8], points[9], img, ref);
}

t_image	draw_cube(t_image img, double a, double j, double k, t_point ref, double norm)
{
	t_point	*cube;
	t_point	*new_cube;
	double	x;
	double	y;
	int i = 0;

	cube = (t_point *)malloc(10 * sizeof(t_point));
	new_cube = (t_point *)malloc(10 * sizeof(t_point));
	init_point(&cube[0], -norm, -norm, 0);
	init_point(&cube[1], 0, -norm, 0);
	init_point(&cube[2], norm, -norm, 0);
	init_point(&cube[3], -norm, 0, 0);
	init_point(&cube[4], 0, 0, 100);
	init_point(&cube[5], norm, 0, 0);
	init_point(&cube[6], -norm, norm, 0);
	init_point(&cube[7], 0, norm, 0);
	init_point(&cube[8], norm, norm, 0);
	cube[9].exists = 0;
	cube = rotate_z(cube, k);
	cube = rotate_y(cube, j);
	cube = rotate_x(cube, a);
	for (; cube[i].exists; i++)
	{
		new_cube[i].x = sqrt(2)/2 * (cube[i].x - cube[i].y);
		new_cube[i].y = sqrt(2.0/3.0) * cube[i].z - 1/sqrt(6) * (cube[i].x + cube[i].y);
		new_cube[i].exists = 1;
	}
	free(cube);
	new_cube[i].exists = 0;
	img = join_points(new_cube, img, ref);
	free(new_cube);
	return img;
}

/*int test3(int x, int y, void* nothing)
{
	printf("%d %d\n", x, y);
	return (0);
}

int test2(int button, int x, int y, t_test *test)
{
	mlx_hook(test->main.win, 04, 0L, test3, test);
	return (0);
}

int test1(int button, int x, int y, t_test *test)
{
	if (button == 1)
		mlx_hook(test->main.win, 06, 0L, test3, &(*test));
	return (0);
}*/

int	main(int argc, char **argv)
{
	t_win	main;
	char	**tab;
	t_image img;
	t_test	test;

	main.mlx = mlx_init();

	img.img = mlx_new_image(main.mlx, 1920, 1080);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	if (main.mlx == 0)
		exit(0);
	main.win = mlx_new_window(main.mlx, WIDTH, HEIGHT, "cube.c");
	
	test.main = main;
	test.img = img;
	test.i = M_PI / 6;
	test.j = M_PI / 6;
	test.k = M_PI / 6;
	test.ref.x = WIDTH / 2;
	test.ref.y = HEIGHT / 2;
	test.norm = 200;

	mlx_mouse_hook(main.win, mouse_hook, &test);

	mlx_hook(main.win, 17, 1L<<17, exit_hook, (void *)0);

	mlx_hook(main.win, 02, 0L, key_hook, &test);

	//mlx_hook(main.win, 04, 1L>>6, test1, &test);

	mlx_do_sync(main.mlx);

	mlx_loop_hook(main.mlx, render_next_frame, &test);

	mlx_loop(main.mlx);
}