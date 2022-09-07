/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rolled.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:30:12 by tlafay            #+#    #+#             */
/*   Updated: 2022/03/18 11:54:04 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROLLED_H
# define ROLLED_H

# include <X11/keysym.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <sys/time.h>
# include "mlx.h"
# include "../srcs/libft/libft.h"
# define G 9.81
# define ESCAPE_KEY 53
# define WIDTH 1920
# define HEIGHT 1080
# define FD 124
# define FG 123
# define FH 126
# define FB 125
# define X_UP 91
# define X_DOWN 84
# define Y_UP 86
# define Y_DOWN 88
# define Z_UP 69
# define Z_DOWN 78
# define W 13
# define S 1
# define A 0
# define D 2

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

t_image		draw_cube(t_image img, double time);
t_image 	draw_ball(int x_mid, int y_mid, int r, t_image img);
int			key_hook(int keycode, t_test *test);
int			exit_hook(int keycode, t_win *main);
int 		render_next_frame(t_test *test);
void		my_mlx_pixel_put(t_image *data, int x, int y, int color);
void		circle_coord(double *x, double *y, int r, double angle);
double		coeff_dir(t_point p1, t_point p2);
double		calc_y(double x, t_point p1, t_point p2);
void		init_point(t_point *point, double x, double y, double z);
t_vector	init_vector(t_point	p1, t_point	p2);
double		trajectory(double t, double angle, double v0, double x0);
double		speed(double t, double angle, double v0);
int			invert_y(int y);

#endif