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
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->frame_buffer.img)
		mlx_destroy_image(data->mlx, data->frame_buffer.img);
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
	data->s_time = ft_gettime();
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


static int	render(t_data *data)
{
	//image_to_fbuff(&data->frame_buffer, &data->creeper, (t_vec2){w, h}, (t_vec2){100, 100});
	// for (int i = 0; i < 20; i++)
		// for (int j = 0; j < 20; j++)
	//square_to_fbuff(&data->frame_buffer, (t_vec2){0, 0}, (t_vec2){WIN_W, WIN_H}, (t_color){255, 255, 0, 0});
	mlx_put_image_to_window(data->mlx, data->win, data->frame_buffer.img, 0, 0);
	print_fps_to_consol();
	return (0);
}

void	cub_loop(t_data *data)
{
	int		w = 128;
	int		h = 128;
	data->creeper.img = mlx_xpm_file_to_image(data->mlx, "./assets/creeper.xpm", &w, &h);
	if (!data->creeper.img)
		cub_exit(data, 1);
	data->creeper.addr = mlx_get_data_addr(data->creeper.img, &data->creeper.bpp,
			&data->creeper.line_length, &data->creeper.endian);
	//***Retire la loop pour check les leak sans ctrl-c***
	mlx_hook(data->win, DestroyNotify, StructureNotifyMask, cub_exit, &data);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop(data->mlx);
	//mlx_destroy_image(data->mlx, data->creeper.img);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc >= 2)
	{
		if (cub_init(&data) != 0)
			cub_exit(&data, EXIT_FAILURE);
		if ((ft_strncmp(argv[1], "EDITOR", 6) == 0) && argc == 3)
			editor_loop(&data, argv);
		//else if ((ft_strncmp(argv[1], "EDITOR", 6) != 0) && argc == 2)
		//	cub_loop(&data);
		//cub_exit(&data, 0);
	}
	return (0);
}
