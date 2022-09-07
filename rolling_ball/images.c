/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:33:03 by tlafay            #+#    #+#             */
/*   Updated: 2022/03/17 13:19:08 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rolled.h"

int	key_hook(int keycode, t_test *test)
{
	if (keycode == ESCAPE_KEY)
		exit(0);
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
	test->img = draw_cube(new_img, (float)time / 1000000);
	mlx_put_image_to_window(test->main.mlx, test->main.win, new_img.img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
