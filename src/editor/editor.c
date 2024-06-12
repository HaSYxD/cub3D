#include <cub3d.h>

t_button *grid = NULL;
int	grid_size;

static int	render(t_data *data)
{
	int	mx, my = 0;

	mlx_mouse_get_pos(data->mlx, data->win, &mx, &my);
	data->mouse_position = (t_vec2){mx, my};
	for (int i = 0; i < grid_size; i++) {
		update_button(&grid[i], data);
	}
	for (int i = 0; i < grid_size; i++) {
		draw_button(grid[i], data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->frame_buffer.img, 0, 0);
	print_fps_to_consol();
	return (0);
}

void	editor_loop(t_data *data, char *argv[])
{
	t_count	c;
	int	scale;
	int	xoffset;

	c = (t_count){-1, ft_atoi(argv[2]), 0};
	if (c.j < 5 || c.j > 30)
	{
		printf("Map size must be between 5 and 30 square wide\n");
		return ;
	}
	grid_size = c.j * c.j;
	grid = malloc(sizeof(*grid) * grid_size);
	scale = WIN_H / (c.j * (WIN_H / 451));
	xoffset = (WIN_W - WIN_H) / 2;
	while (++c.i < grid_size)
		grid[c.i] = get_button((t_rec){(c.i%c.j*scale) + xoffset, (c.i/c.j*scale), scale-1, scale-1},
				(t_color){255, 255, 255, 255}, (t_color){255, 50, 50, 50});
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->creeper.img);
}
