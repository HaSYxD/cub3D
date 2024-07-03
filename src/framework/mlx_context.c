/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_context.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:34:11 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/16 22:34:12 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub_framework.h>

t_img	load_xpm(t_mlxctx *mlx, char *path, int *size)
{
	t_img	image;
	int		res_buff;

	image.img = mlx_xpm_file_to_image(mlx->mlx, path, &res_buff, &res_buff);
	image.addr = mlx_get_data_addr(image.img, &image.bpp,
			&image.line_length, &image.endian);
	if (*size == 0)
		*size = res_buff;
	if (*size > res_buff)
		*size = res_buff;
	return (image);
}

int	start_mlxctx(t_mlxctx *mlx, int (*start_func)(),
	int (*quit_func)(), void *param)
{
	mlx_hook(mlx->win, KeyPress, KeyPressMask, key_press, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, key_release, mlx);
	mlx_hook(mlx->win, ButtonPress, ButtonPressMask, mouse_press, mlx);
	mlx_hook(mlx->win, ButtonRelease, ButtonReleaseMask, mouse_release, mlx);
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, quit_func, param);
	mlx_loop_hook(mlx->mlx, start_func, param);
	mlx_loop(mlx->mlx);
	return (0);
}

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
	mlx->win_w = w;
	mlx->win_h = h;
	mlx->mouse_state = 0;
	mlx->key_state[0] = 0;
	mlx->key_state[1] = 0;
	mlx->key_state[2] = 0;
	mlx->mouse_position = (t_vec2){0, 0};
	mlx->frame_time = 0.01667;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (EXIT_FAILURE);
	mlx->win = mlx_new_window(mlx->mlx, w, h, name);
	if (!mlx->win)
		return (EXIT_FAILURE);
	mlx->frame_buffer.img = mlx_new_image(mlx->mlx, w, h);
	if (!mlx->frame_buffer.img)
		return (EXIT_FAILURE);
	mlx->frame_buffer.addr = mlx_get_data_addr(mlx->frame_buffer.img,
			&mlx->frame_buffer.bpp, &mlx->frame_buffer.line_length,
			&mlx->frame_buffer.endian);
	mlx_set_font(mlx->mlx, mlx->win, FONT);
	return (0);
}
