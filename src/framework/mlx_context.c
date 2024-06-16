#include <cub_framework.h>

int	destroy_mlxctx(t_mlxctx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->frame_buffer.img)
		mlx_destroy_image(mlx->mlx, mlx->frame_buffer.img);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		ft_free(mlx->mlx);
	}
	return (0);
}

int	init_mlxctx(t_mlxctx *mlx, int w, int h, char *name)
{
	int	init_status;

	init_status = 0;
	mlx->win_w = w;
	mlx->win_h = h;
	mlx->mouse_state = 0;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		init_status = EXIT_FAILURE;
	if (init_status != EXIT_FAILURE)
		mlx->win = mlx_new_window(mlx->mlx, w, h, name);
	if (!mlx->win)
		init_status = EXIT_FAILURE;
	if (init_status != EXIT_FAILURE)
		mlx->frame_buffer.img = mlx_new_image(mlx->mlx, w, h);
	if (!mlx->frame_buffer.img)
		init_status = EXIT_FAILURE;
	mlx->frame_buffer.addr = mlx_get_data_addr(mlx->frame_buffer.img,
			&mlx->frame_buffer.bpp, &mlx->frame_buffer.line_length,
			&mlx->frame_buffer.endian);
	if (!mlx->frame_buffer.addr)
		init_status = EXIT_FAILURE;
	if (init_status != EXIT_FAILURE)
		mlx_set_font(mlx->mlx, mlx->win, FONT);
	return (init_status);
}
