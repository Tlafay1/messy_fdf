/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:24:55 by tlafay            #+#    #+#             */
/*   Updated: 2022/01/14 14:04:10 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	moves(t_data *data, int keycode)
{
	if (keycode == X_UP)
		data->system.i += M_PI / 48;
	if (keycode == X_DOWN)
		data->system.i -= M_PI / 48;
	if (keycode == Y_UP)
		data->system.j += M_PI / 48;
	if (keycode == Y_DOWN)
		data->system.j -= M_PI / 48;
	if (keycode == Z_UP)
		data->system.k += M_PI / 48;
	if (keycode == Z_DOWN)
		data->system.k -= M_PI / 48;
	if (keycode == D)
		data->system.ref.x += 10;
	if (keycode == A)
		data->system.ref.x -= 10;
	if (keycode == W)
		data->system.ref.y -= 10;
	if (keycode == S)
		data->system.ref.y += 10;
}

int	key_hook(unsigned int keycode, t_data *data)
{
	if (keycode == ESCAPE_KEY)
	{
		mlx_destroy_window(data->main.mlx, data->main.win);
		exit(0);
	}
	moves(data, keycode);
	if (keycode == 15)
		init_view(data);
	if (keycode == 9)
	{
		if (data->proj == 1)
			data->proj = 2;
		else
			data->proj = 1;
	}
	data->modified = 1;
	return (0);
}

int	mouse_hook(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 4)
		data->system.norm += 1;
	if (button == 5 && data->system.norm >= 1)
		data->system.norm -= 1;
	data->modified = 1;
	return (0);
}

int	exit_hook(unsigned int keycode, t_win *main)
{
	(void)main;
	(void)keycode;
	exit(0);
}

int	render_next_frame(t_data *data)
{
	t_image	new_img;

	if (data->modified == 0)
		return (0);
	new_img.img = mlx_new_image(data->main.mlx, WIDTH, HEIGHT);
	new_img.addr = mlx_get_data_addr(new_img.img,
			&new_img.bits_per_pixel, &new_img.line_length, &new_img.endian);
	mlx_destroy_image(data->main.mlx, data->img.img);
	if (data->system.i > M_PI * 2)
		data->system.i -= M_PI * 2;
	if (data->system.j > M_PI * 2)
		data->system.j -= M_PI * 2;
	if (data->system.k > M_PI * 2)
		data->system.k -= M_PI * 2;
	if (data->system.i < 0)
		data->system.i += M_PI * 2;
	if (data->system.j < 0)
		data->system.j += M_PI * 2;
	if (data->system.k < 0)
		data->system.k += M_PI * 2;
	new_img = draw_frame(new_img, data->system, data->proj);
	mlx_put_image_to_window(data->main.mlx, data->main.win, new_img.img, 0, 0);
	data->img = new_img;
	data->modified = 0;
	return (0);
}
