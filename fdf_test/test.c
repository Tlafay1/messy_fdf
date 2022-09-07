#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define MLX_ERROR 1

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int	handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int handle_other_keypress(int x, int y, t_data *data)
{
	printf("%d %d\n", x, y);
	return (0);
}

int	handle_keypress(int keysym, int x, int y, t_data *data)
{
	if (keysym == 53)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);

	if (keysym == 1)
		mlx_hook(data->win_ptr, 12, 1L<<6, &handle_other_keypress, data);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */ 
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &handle_keypress, &data); /* ADDED */
	mlx_hook(data.win_ptr, ButtonRelease, ButtonReleaseMask, &handle_keyrelease, &data); /* CHANGED */

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	//mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}