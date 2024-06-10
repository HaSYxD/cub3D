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

static int	cub_exit(t_data *data, int exit_status)
{
	if (data->frame_buffer.img)
		mlx_destroy_image(data->mlx, data->frame_buffer.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		ft_free(data->mlx);
	}
	exit (exit_status);
}

static int	cub_init(t_data *data)
{
	int	init_status;

	init_status = 0;
	data->mlx = mlx_init();
	if (!data->mlx)
		init_status = EXIT_FAILURE;
	if (init_status != EXIT_FAILURE)
		data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, WIN_N);
	if (!data->win)
		init_status = EXIT_FAILURE;
	if (init_status != EXIT_FAILURE)
		data->frame_buffer.img = mlx_new_image(data->mlx, WIN_W, WIN_H);
	if (!data->frame_buffer.img)
		init_status = EXIT_FAILURE;
	data->frame_buffer.addr = mlx_get_data_addr(data->frame_buffer.img,
			&data->frame_buffer.bpp, &data->frame_buffer.line_length,
			&data->frame_buffer.endian);
	if (!data->frame_buffer.addr)
		init_status = EXIT_FAILURE;
	return (init_status);
}

static void	cub_loop(t_data *data)
{
	t_img	creeper;
	int		w = 800;
	int		h = 600;

	creeper.img = mlx_xpm_file_to_image(data->mlx, "./assets/creeper.xpm", &w, &h);
	if (!creeper.img)
		cub_exit(data, 1);
	creeper.addr = mlx_get_data_addr(creeper.img, &creeper.bpp,
			&creeper.line_length, &creeper.endian);
	image_to_fbuff(&data->frame_buffer, &creeper, (t_vec2){w, h}, (t_vec2){0, 200});
	square_to_fbuff(&data->frame_buffer, (t_vec2){20, 20}, (t_vec2){50, 50}, (t_color){255, 255, 0, 0});
	circle_to_fbuff(&data->frame_buffer, (t_vec2){200, 200}, 100, (t_color){255, 255, 0, 0});
	mlx_put_image_to_window(data->mlx, data->win, data->frame_buffer.img, 0, 0);
	//***Retire la loop pour check les leak sans ctrl-c***
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, creeper.img);
}

int	main(void)
{
	t_data	data;

	data = (t_data){0};
	if (cub_init(&data) != 0)
		cub_exit(&data, EXIT_FAILURE);
	cub_loop(&data);
	cub_exit(&data, 0);
}
