/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:03:30 by aliaudet          #+#    #+#             */
/*   Updated: 2024/06/07 01:03:32 by aliaudet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	render(t_mlxctx *mlx)
{
	//image_to_fbuff(&data->frame_buffer, &data->creeper, (t_vec2){w, h}, (t_vec2){100, 100});
	// for (int i = 0; i < 20; i++)
		// for (int j = 0; j < 20; j++)
	//square_to_fbuff(&data->frame_buffer, (t_vec2){0, 0}, (t_vec2){WIN_W, WIN_H}, (t_color){255, 255, 0, 0});
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->frame_buffer.img, 0, 0);
	print_fps_to_consol();
	return (0);
}

void	run_cub3d(t_mlxctx *mlx)
{
	/*int		w = 128;
	int		h = 128;
	data->creeper.img = mlx_xpm_file_to_image(data->mlx, "./assets/creeper.xpm", &w, &h);
	if (!data->creeper.img)
		cub_exit(data, 1);
	data->creeper.addr = mlx_get_data_addr(data->creeper.img, &data->creeper.bpp,
			&data->creeper.line_length, &data->creeper.endian);*/
	//***Retire la loop pour check les leak sans ctrl-c***
	mlx_hook(mlx->win, DestroyNotify, StructureNotifyMask, destroy_mlxctx, mlx);
	mlx_loop_hook(mlx->mlx, &render, mlx);
	mlx_loop(mlx->mlx);
	//mlx_destroy_image(data->mlx, data->creeper.img);
}
