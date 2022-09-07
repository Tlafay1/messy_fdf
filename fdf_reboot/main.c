/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafay <tlafay@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:05:09 by tlafay            #+#    #+#             */
/*   Updated: 2022/01/14 14:13:28 by tlafay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_view(t_data *data)
{
	data->system.i = M_PI / 1.116279;
	data->system.j = M_PI / 0.527473;
	data->system.k = M_PI / 2.823529;
	data->system.ref.x = WIDTH / 2;
	data->system.ref.y = HEIGHT / 2;
	data->modified = 1;
}

void	errors(int argc)
{
	if (argc != 2)
	{
		write(1, "Usage: ./fdf <file.fdf>\n", 24);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	errors(argc);
	data.main.mlx = mlx_init();
	if (!data.main.mlx)
		exit(1);
	data.img.img = mlx_new_image(data.main.mlx, 1920, 1080);
	if (!data.img.img)
		exit(1);
	data.img.addr = mlx_get_data_addr(data.img.img,
			&data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);
	data.main.win = mlx_new_window(data.main.mlx, WIDTH, HEIGHT, "cube.c");
	if (!data.main.win)
		exit(1);
	init_view(&data);
	data.proj = 1;
	data.system = get_map(argv[1], data.system);
	data.system.norm = (data.system.width + 130) * (data.system.height + 90)
		/ (data.system.width * data.system.height);
	mlx_mouse_hook(data.main.win, mouse_hook, &data);
	mlx_hook(data.main.win, 17, 1L << 17, exit_hook, NULL);
	mlx_hook(data.main.win, 02, 0L, key_hook, &data);
	mlx_do_sync(data.main.mlx);
	mlx_loop_hook(data.main.mlx, render_next_frame, &data);
	mlx_loop(data.main.mlx);
}
