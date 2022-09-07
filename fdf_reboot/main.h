/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:48:35 by tlafay            #+#    #+#             */
/*   Updated: 2022/01/14 14:02:28 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include "mlx.h"
# include "../srcs/libft/libft.h"
# include <sys/time.h>
# define ESCAPE_KEY 53
# define WIDTH 1920
# define HEIGHT 1080
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

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_win
{
	void	*mlx;
	void	*win;
}				t_win;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		exists;
}				t_point;

typedef struct s_vector
{
	t_point	p1;
	t_point	p2;
	int		norm;
	int		dx;
	int		dy;
	int		dz;
	int		sx;
	int		sy;
	int		sz;
	int		dm;
	int		e2;
}				t_vector;

typedef struct s_system
{
	double	i;
	double	j;
	double	k;
	double	norm;
	int		height;
	int		width;
	t_point	ref;
	t_point	*map;
}				t_system;

typedef struct s_data
{
	t_image		img;
	t_win		main;
	t_system	system;
	int			modified;
	int			proj;
}			t_data;

t_image		plot_line(t_vector vector, t_image img, t_point ref);
t_image		join_points(t_point *points, t_image img, t_system system);
t_image		draw_frame(t_image img, t_system system, int proj);
void		my_mlx_pixel_put(t_image *data, int x, int y, int color);
void		init_point(t_point *point, double x, double y, double z);
t_vector	init_vector(t_point	p1, t_point	p2);
t_point		*rotate_x(t_point *point, double angle);
t_point		*rotate_y(t_point *point, double angle);
t_point		*rotate_z(t_point *point, double angle);
int			key_hook(unsigned int keycode, t_data *data);
int			mouse_hook(int button, int x, int y, t_data *data);
int			exit_hook(unsigned int keycode, t_win *main);
int			render_next_frame(t_data *data);
void		init_view(t_data *data);
t_system	get_map(char *filename, t_system system);
int			point_len(t_point *map);

#endif
